#ifndef CONNECTIONITEM_H
#define CONNECTIONITEM_H

#include "qgraphicsitem.h"
#include "qpoint.h"

class PortItem;

class ConnectionItem : public QGraphicsPathItem
{
public:
    ConnectionItem(PortItem* from, PortItem* to);

    void updatePath();

private:
    PortItem* m_from;
    PortItem* m_to;
};

#endif // CONNECTIONITEM_H
