#ifndef CONNECTIONITEM_H
#define CONNECTIONITEM_H

#include <QGraphicsPathItem>
#include "portitem.h"

class ConnectionItem : public QGraphicsPathItem
{
public:
    ConnectionItem(PortItem* from, PortItem* to);

    void updatePath();

    PortItem* sourcePort() const { return m_from; }
    PortItem* targetPort() const { return m_to; }

private:
    PortItem* m_from;
    PortItem* m_to;
};



#endif // CONNECTIONITEM_H
