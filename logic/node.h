#ifndef NODE_H
#define NODE_H

#include "qdebug.h"
#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <QVector>
#include <functional>
#include <type_traits>

#include "../NodeContext.h"
#include "Port.h"

class IVna;

class Node
{
public:
    using Callback = std::function<bool(const QVariantMap &params,
                                        const QHash<QUuid, QVariant> &inputs,
                                        NodeContext &ctx,
                                        QString &error,
                                        QHash<QUuid, QVariant> &outputs)>;

    explicit Node(const QString &name = {}, Callback cb = {});
    virtual ~Node() = default;

    QString name() const;
    QVariantMap &params();

    virtual bool execute(const QHash<QUuid, QVariant> &inputs,
                         NodeContext &ctx,
                         QString &error,
                         QHash<QUuid, QVariant> &outputs);

    const QHash<QUuid, QVariant> &lastOutput() const;

    // -------- Ports --------
    QVector<Port> inputs() const;
    QVector<Port> outputs() const;

    int countInputsPorts() const;
    int countOutputsPorts() const;

    void setInputs(const QVector<Port> &inputs);
    void setOutputs(const QVector<Port> &outputs);

protected:
    QString _name;
    QVariantMap _params;
    Callback _callback;

    QVector<Port> _inputs;
    QVector<Port> _outputs;

    QHash<QUuid, QVariant> _lastOutput;
};

// ===================== StartNode =====================
class StartNode : public Node
{
public:
    explicit StartNode() : Node("Start")
    {}

    bool execute(const QHash<QUuid, QVariant> &,
                 NodeContext &,
                 QString &,
                 QHash<QUuid, QVariant> &) override
    {
        qInfo() << "start";
        return true;
    }
};

#endif // NODE_H
