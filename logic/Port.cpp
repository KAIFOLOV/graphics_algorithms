#include "Port.h"

Port::Port(Type type, const QString &name) : _id(QUuid::createUuid()), _type(type), _name(name)
{}

Port::Port(Type type, Direction direction, const QString &name) :
    _id(QUuid::createUuid()),
    _type(type),
    _direction(direction),
    _name(name)
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

Port::Direction Port::direction() const
{
    return _direction;
}

void Port::setDirection(Port::Direction newDirection)
{
    _direction = newDirection;
}
