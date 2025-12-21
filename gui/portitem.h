#ifndef PORTITEM_H
#define PORTITEM_H

#include <QGraphicsEllipseItem>
#include <QVector>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>

class ConnectionItem;
class NodeItem;

class PortItem : public QGraphicsEllipseItem
{
public:
    enum class Direction { Input, Output };
    enum class PortKind { Data, Control };

    PortItem(Direction dir, PortKind kind, QGraphicsItem* parentNode)
        : QGraphicsEllipseItem(parentNode), m_dir(dir), m_kind(kind), m_tempLine(nullptr)
    {
        setRect(-5,-5,10,10);
        setBrush(dir == Direction::Input ? Qt::blue : Qt::green);
        setFlag(QGraphicsItem::ItemIsSelectable);
        setAcceptHoverEvents(true);
    }

    Direction getDirection() const { return m_dir; }
    PortKind kind() const { return m_kind; }

    QPointF sceneCenter() const { return mapToScene(rect().center()); }

    void addConnection(ConnectionItem* conn);
    const QVector<ConnectionItem*>& connections() const { return m_connections; }

    void setIndex(int index) {
        _index = index;
    }

    NodeItem *parentNodeItem() const;

    int index() const
    {
        return _index;
    }

    bool canAcceptConnection() const;
    void removeConnection(ConnectionItem *c);

protected:
    void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    Direction m_dir;
    PortKind  m_kind;

    QVector<ConnectionItem*> m_connections;

    QGraphicsLineItem* m_tempLine;

    int _index;
};

#endif // PORTITEM_H
