#ifndef PORTITEM_H
#define PORTITEM_H

#include <QGraphicsEllipseItem>
#include <QVector>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>

#include "../NodePort.h"

class ConnectionItem;
class NodeItem;

class PortItem : public QGraphicsEllipseItem
{
public:
    enum class Direction
    {
        Input,
        Output
    };
    enum class PortKind
    {
        Data,
        Control
    };

    PortItem(Direction dir, PortKind kind, QGraphicsItem *parentNode) :
        QGraphicsEllipseItem(parentNode),
        m_dir(dir),
        m_kind(kind),
        m_tempLine(nullptr)
    {
        setRect(-5, -5, 10, 10);
        setBrush(dir == Direction::Input ? Qt::blue : Qt::green);
        setFlag(QGraphicsItem::ItemIsSelectable);
        setAcceptHoverEvents(true);
    }

    Direction getDirection() const
    {
        return m_dir;
    }
    PortKind kind() const
    {
        return m_kind;
    }

    QPointF sceneCenter() const
    {
        return mapToScene(rect().center());
    }

    void addConnection(ConnectionItem *conn);
    const QVector<ConnectionItem *> &connections() const
    {
        return m_connections;
    }

    void setPortId(const PortId &id)
    {
        m_portId = id;
    }
    PortId portId() const
    {
        return m_portId;
    }

    NodeItem *parentNodeItem() const;

    bool canAcceptConnection() const;
    void removeConnection(ConnectionItem *c);

protected:
    void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Direction m_dir;
    PortKind m_kind;

    QVector<ConnectionItem *> m_connections;

    QGraphicsLineItem *m_tempLine;

    PortId m_portId;
};

#endif // PORTITEM_H
