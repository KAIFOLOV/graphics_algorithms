#include "Edge.h"

Edge::Edge(Port *from, Port *to) : _from(from), _to(to)
{}

Port *Edge::from() const
{
    return _from;
}

void Edge::setFrom(Port *newFrom)
{
    _from = newFrom;
}

Port *Edge::to() const
{
    return _to;
}

void Edge::setTo(Port *newTo)
{
    _to = newTo;
}

bool Edge::isControl() const
{
    return _from->type() == Port::Type::Control && _to->type() == Port::Type::Control;
}
