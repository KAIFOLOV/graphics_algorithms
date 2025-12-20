#ifndef NODEITEM_H
#define NODEITEM_H

#include "portitem.h"
#include <QGraphicsObject>
#include <QVector>

class Node;
class ConnectionItem;

class NodeItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit NodeItem(Node* node);

    QRectF boundingRect() const override;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

    PortItem* inputPort() const { return m_input; }
    PortItem* outputPort() const { return m_output; }

    Node* node() const;

    void addConnection(ConnectionItem* conn) { m_connections.append(conn); }
    const QVector<ConnectionItem*>& connections() const { return m_connections; }

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Node* m_node = nullptr;
    PortItem* m_input = nullptr;
    PortItem* m_output = nullptr;
    QVector<ConnectionItem*> m_connections; // все соединения этой ноды
};

#endif // NODEITEM_H
