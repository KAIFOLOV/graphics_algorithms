#ifndef NODE_H
#define NODE_H

#include "qdebug.h"
#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <QVector>
#include <functional>
#include <typeindex>
#include <unordered_map>
#include <type_traits>

class IVna;

class NodeContext
{
public:
    template<typename T>
    void set(T* device) { devices[typeid(T)] = device; }

    template<typename T>
    T* get() const
    {
        auto it = devices.find(typeid(T));
        if (it == devices.end())
            return nullptr;
        return static_cast<T*>(it->second);
    }

private:
    std::unordered_map<std::type_index, void*> devices;
};

class Node : public QObject
{
    Q_OBJECT
public:
    using Callback = std::function<bool(
        const QVariantMap& params,
        const QVector<QVariant>& inputs,
        NodeContext& ctx,
        QString& error,
        QVector<QVariant>& outputs
        )>;

    explicit Node() = default;

    explicit Node(const QString& name, Callback cb, QObject* parent = nullptr);

    virtual QString name() const { return m_name; }
    QVariantMap& params() { return m_params; }

    virtual bool execute(const QVector<QVariant>& inputs, NodeContext& ctx, QString& error, QVector<QVariant>& outputs)
    {
        bool ok = m_cb(m_params, inputs, ctx, error, outputs);
        if (ok)
            m_lastOutput = outputs;
        return ok;
    }

    const QVector<QVariant>& lastOutput() const { return m_lastOutput; }

    int countInputsPorts() const;
    void setCountInputsPorts(int newCountInputsPorts);

    int countOutputsPorts() const;
    void setCountOutputsPorts(int newCountOutputsPorts);

signals:
    void updated();

private:
    QString m_name;
    QVariantMap m_params;
    Callback m_cb;
    QVector<QVariant> m_lastOutput;

    int _countInputsPorts { 0 };
    int _countOutputsPorts { 0 };
};

class StartNode : public Node
{
public:
    explicit StartNode() = default;
    QString name() const override { return "Start"; }

    bool execute(const QVector<QVariant>&,
                 NodeContext&,
                 QString&,
                 QVector<QVariant>&) override
    {
        qInfo() << "start";
        return true; // ничего не делает
    }
};

// ===================== MethodNodeFactoryHybrid =====================
template<typename T>
struct MethodNodeFactoryHybrid;

template<typename Device, typename R, typename... Args>
struct MethodNodeFactoryHybrid<R(Device::*)(Args...)>
{
    static Node::Callback make(R(Device::*method)(Args...))
    {
        return [method](const QVariantMap& params,
                        const QVector<QVariant>& inputs,
                        NodeContext& ctx,
                        QString& error,
                        QVector<QVariant>& outputs) -> bool
        {
            Device* dev = ctx.get<Device>();
            if (!dev) {
                error = QString("Device not found: %1").arg(typeid(Device).name());
                return false;
            }

            if (inputs.size() > sizeof...(Args)) {
                error = "Too many inputs";
                // return false;
            }

            call(method, dev, params, inputs, outputs,
                 std::index_sequence_for<Args...>{});
            return true;
        };
    }

private:
    template<std::size_t... I>
    static void call(R(Device::*method)(Args...),
                     Device* dev,
                     const QVariantMap& params,
                     const QVector<QVariant>& inputs,
                     QVector<QVariant>& outputs,
                     std::index_sequence<I...>)
    {
        auto getArg = [&](size_t i, auto /*typeTag*/) -> QVariant {
            if (i < inputs.size())
                return inputs[i];
            else
                return params.value(QString("arg%1").arg(i));
        };

        if constexpr (std::is_void_v<R>) {
            (dev->*method)(getArg(I, (Args*)nullptr).template value<Args>()...);
        } else {
            R r = (dev->*method)(getArg(I, (Args*)nullptr).template value<Args>()...);
            outputs = { QVariant::fromValue(r) };
        }
    }
};

#endif // NODE_H
