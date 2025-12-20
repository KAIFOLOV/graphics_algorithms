#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <QVector>
#include <functional>

class IVna;

struct NodeContext
{
    IVna* vna = nullptr;
};

class Node : public QObject
{
    Q_OBJECT
public:
    // новый Callback: входные данные и выходные данные
    using Callback = std::function<bool(
        const QVariantMap& params,
        const QVector<QVariant>& inputs,
        NodeContext& ctx,
        QString& error,
        QVector<QVariant>& outputs
        )>;

    explicit Node(const QString& name, Callback cb, QObject* parent = nullptr);

    QString name() const;
    QVariantMap& params();

    // execute с передачей входных данных и возвратом выходных
    bool execute(const QVector<QVariant>& inputs, NodeContext& ctx, QString& error, QVector<QVariant>& outputs);

    const QVector<QVariant>& lastOutput() const { return m_lastOutput; }

signals:
    void updated();

private:
    QString m_name;
    QVariantMap m_params;
    Callback m_cb;
    QVector<QVariant> m_lastOutput;
};

#endif // NODE_H
