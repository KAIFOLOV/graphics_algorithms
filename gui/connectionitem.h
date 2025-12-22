#ifndef CONNECTIONITEM_H
#define CONNECTIONITEM_H

#include <QGraphicsPathItem>
#include "portitem.h"
#include "../Connection.h"

class ConnectionItem : public QGraphicsPathItem
{
public:
    ConnectionItem(const Connection& model, PortItem* from, PortItem* to);

    void updatePath();

    void disconnect();

    const Connection& model() const { return m_model; }

    PortItem* sourcePort() const { return m_from; }
    PortItem* targetPort() const { return m_to; }

private:
    Connection m_model;
    PortItem* m_from;
    PortItem* m_to;
};



#endif // CONNECTIONITEM_H
