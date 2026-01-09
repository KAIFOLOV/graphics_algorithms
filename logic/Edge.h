#ifndef EDGE_H
#define EDGE_H

#include "node.h"

class Edge
{
public:
    explicit Edge() = default;
    explicit Edge(Port *from, Port *to);

    Port *from() const;
    void setFrom(Port *newFrom);

    Port *to() const;
    void setTo(Port *newTo);

private:
    Port *_from;
    Port *_to;
};

#endif // EDGE_H
