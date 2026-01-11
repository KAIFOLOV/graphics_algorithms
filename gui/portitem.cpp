#include "portitem.h"
#include "GraphItem.h"
#include "qpainter.h"
#include <QGraphicsScene>

#include "../logic/Edge.h"

PortItem::PortItem(Port *port, QGraphicsItem *parentNode) :
    QGraphicsEllipseItem(parentNode),
    _port(port),
    _tempLine(nullptr)
{
    setRect(-5, -5, 10, 10);
    setBrush(_port->direction() == Port::Direction::Input ? Qt::blue : Qt::green);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
}

QUuid PortItem::portId() const
{
    return _port->id();
}

void PortItem::addConnection(EdgeItem *edge)
{
    _connections.append(edge);
}

void PortItem::removeConnection(EdgeItem *edge)
{
    _connections.removeOne(edge);
}

const QList<EdgeItem *> &PortItem::connections() const
{
    return _connections;
}

Port::Direction PortItem::getDirection() const
{
    return _port->direction();
}

Port::Type PortItem::getType() const
{
    return _port->type();
}

QPointF PortItem::sceneCenter() const
{
    return mapToScene(rect().center());
}

Port *PortItem::port() const
{
    return _port;
}

void PortItem::paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *)
{
    QColor color;
    if (getType() == Port::Type::Control) {
        color =
         (getDirection() == Port::Direction::Input) ? QColor(180, 80, 80) : QColor(220, 50, 50);
    } else {
        color =
         (getDirection() == Port::Direction::Input) ? QColor(80, 80, 180) : QColor(50, 180, 50);
    }

    p->setBrush(color);
    p->setPen(Qt::black);
    p->drawEllipse(boundingRect());
}

void PortItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    if (!_connections.isEmpty()) {
        auto *gs = qobject_cast<GraphItem *>(scene());
        if (gs) {
            // Копия списка, потому что removeConnection() меняет _connections
            auto tmp = _connections;
            for (auto *edge : tmp) gs->removeEdge(edge);
        }
    }

    _tempLine = new QGraphicsLineItem(QLineF(sceneCenter(), sceneCenter()));
    scene()->addItem(_tempLine);
    event->accept();
}

void PortItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!_tempLine)
        return;

    QLineF line(_tempLine->line().p1(), event->scenePos());
    _tempLine->setLine(line);
}

void PortItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (!_tempLine)
        return;

    // ищем порт под курсором
    PortItem *target = nullptr;
    const auto items = scene()->items(event->scenePos());
    for (auto *it : items) {
        auto *p = qgraphicsitem_cast<PortItem *>(it);
        if (!p || p == this)
            continue;

        target = p;
        break;
    }

    scene()->removeItem(_tempLine);
    delete _tempLine;
    _tempLine = nullptr;

    if (!target)
        return;

    auto *graphItem = qobject_cast<GraphItem *>(scene());
    if (graphItem) {
        graphItem->createEdge(this, target);
    }
}
