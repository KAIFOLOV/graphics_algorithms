#include "Port.h"

Port::Port(Type type, const QString &name) : _type(type), _name(name)
{}

QUuid Port::id() const
{
    return _id;
}

Port::Type Port::type() const
{
    return _type;
}

void Port::setType(Port::Type newType)
{
    _type = newType;
}

QString Port::name() const
{
    return _name;
}

void Port::setName(const QString &newName)
{
    _name = newName;
}
