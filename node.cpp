#include "node.h"

Node::Node(const QString &name, Callback cb)
    : _name(name), _callback(cb)
{}

QString Node::name() const {
    return _name;
}

QVariantMap &Node::params() {
    return _params;
}

bool Node::execute(
    const QHash<PortId, QVariant>& inputs,
    NodeContext& ctx,
    QString& error,
    QHash<PortId, QVariant>& outputs)
{
    if (!_callback)
        return true;

    bool ok = _callback(_params, inputs, ctx, error, outputs);
    if (ok)
        _lastOutput = outputs;

    return ok;
}

const QHash<PortId, QVariant> &Node::lastOutput() const {
    return _lastOutput;
}

int Node::countInputsPorts() const
{
    return _inputs.count();
}

int Node::countOutputsPorts() const
{
    return _outputs.count();
}

QVector<NodePort> Node::inputs() const
{
    return _inputs;
}

void Node::setInputs(const QVector<NodePort> &newInputs)
{
    _inputs = newInputs;
}

QVector<NodePort> Node::outputs() const
{
    return _outputs;
}

void Node::setOutputs(const QVector<NodePort> &newOutputs)
{
    _outputs = newOutputs;
}
