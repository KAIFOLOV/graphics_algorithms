#include "node.h"

Node::Node(const QString &name, Callback cb, QObject *parent)
    : QObject(parent), m_name(name), m_cb(cb)
{}

int Node::countInputsPorts() const
{
    return _countInputsPorts;
}

void Node::setCountInputsPorts(int newCountInputsPorts)
{
    _countInputsPorts = newCountInputsPorts;
}

int Node::countOutputsPorts() const
{
    return _countOutputsPorts;
}

void Node::setCountOutputsPorts(int newCountOutputsPorts)
{
    _countOutputsPorts = newCountOutputsPorts;
}
