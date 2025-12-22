#include "NodePort.h"

NodePort::NodePort(const QString &name) : _name(name)
{}

PortId NodePort::id() const
{
    return _id;
}
