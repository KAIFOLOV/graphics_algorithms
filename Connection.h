#ifndef CONNECTION_H
#define CONNECTION_H

#include "node.h"

struct Connection
{
    Node *from;
    PortId outPort;
    Node *to;
    PortId inPort;

    enum class Type
    {
        Control,
        Data
    } type;
};

#endif // CONNECTION_H
