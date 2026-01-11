#include "Node.h"

Node::Node(const QString &name, Callback cb) : _name(name), _callback(cb)
{
    _controlInput = new Port(Port::Type::Control, Port::Direction::Input, "control input");
    _controlOutput = new Port(Port::Type::Control, Port::Direction::Output, "control output");
}

QString Node::name() const
{
    return _name;
}

QVariantMap &Node::params()
{
    return _params;
}

bool Node::execute(const QHash<QUuid, QVariant> &inputs,
                   NodeContext &ctx,
                   QHash<QUuid, QVariant> &outputs)
{
    if (!_callback)
        return true;

    bool ok = _callback(_params, inputs, ctx, outputs);
    if (ok)
        _lastOutput = outputs;

    return ok;
}

const QHash<QUuid, QVariant> &Node::lastOutput() const
{
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

QVector<Port *> Node::inputs() const
{
    return _inputs;
}

QVector<Port *> Node::outputs() const
{
    return _outputs;
}

void Node::addInput(Port *port)
{
    port->setDirection(Port::Direction::Input);
    _inputs.append(port);
}

void Node::addOutput(Port *port)
{
    port->setDirection(Port::Direction::Output);
    _outputs.append(port);
}

Port *Node::controlInput() const
{
    return _controlInput;
}

Port *Node::controlOutput() const
{
    return _controlOutput;
}
