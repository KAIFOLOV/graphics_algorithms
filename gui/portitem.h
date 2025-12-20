#ifndef PORTITEM_H
#define PORTITEM_H

#include <QGraphicsEllipseItem>
#include <QVector>
#include <QBrush>

class NodeItem;
class ConnectionItem;

class PortItem : public QGraphicsEllipseItem
{
public:
    enum class Direction { Input, Output };

    PortItem(Direction dir, QGraphicsItem* parent = nullptr)
        : QGraphicsEllipseItem(parent), m_dir(dir), m_index(0)
    {
        setRect(-5, -5, 10, 10);
        setBrush(dir == Direction::Input ? Qt::blue : Qt::green);
    }

    Direction getDirection() const { return m_dir; }
    QPointF sceneCenter() const { return mapToScene(rect().center()); }

    void addConnection(ConnectionItem* conn) { m_connections.append(conn); }
    const QVector<ConnectionItem*>& connections() const { return m_connections; }

    // возвращает NodeItem, которому принадлежит порт
    NodeItem* parentNodeItem() const;

    // индекс порта в массиве входных/выходных портов ноды
    void setIndex(int idx) { m_index = idx; }
    int index() const { return m_index; }

private:
    Direction m_dir;
    QVector<ConnectionItem*> m_connections;
    int m_index; // индекс порта в массиве NodeItem
};

#endif // PORTITEM_H
