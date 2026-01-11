#ifndef EDGEITEM_H
#define EDGEITEM_H

#include <QGraphicsPathItem>
#include "portitem.h"
#include "../logic/Edge.h"

class EdgeItem : public QGraphicsPathItem
{
public:
    EdgeItem(Edge *edge, PortItem *from, PortItem *to);

    void updatePath();

    Edge *edge() const;

    PortItem *sourcePort() const;
    PortItem *targetPort() const;

private:
    Edge *_edge;
    PortItem *_from;
    PortItem *_to;
};

#endif // EDGEITEM_H
