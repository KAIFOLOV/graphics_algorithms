#ifndef NODE_H
#define NODE_H

#include "qdebug.h"
#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <QVector>
#include <functional>
#include <type_traits>

#include "NodeContext.h"
#include "NodePort.h"

class IVna;

class Node
{
public:
    using Callback = std::function<bool(
        const QVariantMap& params,
        const QHash<PortId, QVariant>& inputs,
        NodeContext& ctx,
        QString& error,
        QHash<PortId, QVariant>& outputs
        )>;

    explicit Node(const QString& name = {}, Callback cb = {});

    virtual ~Node() = default;

    QString name() const;

    QVariantMap& params();

    virtual bool execute(
        const QHash<PortId, QVariant>& inputs,
        NodeContext& ctx,
        QString& error,
        QHash<PortId, QVariant>& outputs);

    const QHash<PortId, QVariant>& lastOutput() const;

    // -------- Ports --------
    QVector<NodePort> inputs() const;
    QVector<NodePort> outputs() const;

    int countInputsPorts() const;
    int countOutputsPorts() const;

    void setInputs(const QVector<NodePort>& inputs);
    void setOutputs(const QVector<NodePort>& outputs);

protected:
    QString _name;
    QVariantMap _params;
    Callback _callback;

    QVector<NodePort> _inputs;
    QVector<NodePort> _outputs;

    QHash<PortId, QVariant> _lastOutput;
};

// ===================== StartNode =====================
class StartNode : public Node
{
public:
    explicit StartNode()
        : Node("Start")
    {}

    bool execute(
        const QHash<PortId, QVariant>&,
        NodeContext&,
        QString&,
        QHash<PortId, QVariant>&) override
    {
        qInfo() << "start";
        return true;
    }
};

// ===================== MethodNodeFactoryHybrid =====================
template<typename T>
struct MethodNodeFactoryHybrid;

// -------- Method specialization --------
template<typename Device, typename R, typename... Args>
struct MethodNodeFactoryHybrid<R(Device::*)(Args...)>
{
    static Node::Callback make(R(Device::*method)(Args...))
    {
        return [method](
                   const QVariantMap& params,
                   const QHash<PortId, QVariant>& inputs,
                   NodeContext& ctx,
                   QString& error,
                   QHash<PortId, QVariant>& outputs
                   ) -> bool
        {
            Device* dev = ctx.get<Device>();
            if (!dev) {
                error = QString("Device not found: %1").arg(typeid(Device).name());
                return false;
            }

            QVector<QVariant> orderedInputs = inputs.values().toVector();

            try {
                call(method, dev, params, orderedInputs, outputs,
                     std::index_sequence_for<Args...>{});
            }
            catch (...) {
                error = "Method invocation failed";
                return false;
            }

            return true;
        };
    }

private:
    template<std::size_t... I>
    static void call(
        R(Device::*method)(Args...),
        Device* dev,
        const QVariantMap& params,
        const QVector<QVariant>& inputs,
        QHash<PortId, QVariant>& outputs,
        std::index_sequence<I...>
        )
    {
        auto getArg = [&](int i) -> QVariant {
            if (i < inputs.size())
                return inputs[i];
            return params.value(QString("arg%1").arg(i));
        };

        if constexpr (std::is_void_v<R>) {
            (dev->*method)(getArg(I).template value<Args>()...);
        } else {
            R r = (dev->*method)(getArg(I).template value<Args>()...);
            outputs.insert(QUuid::createUuid(), QVariant::fromValue(r));
        }
    }
};

#endif // NODE_H
