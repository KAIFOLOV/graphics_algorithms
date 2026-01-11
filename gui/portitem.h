#ifndef PORTITEM_H
#define PORTITEM_H

#include "../logic/Port.h"

#include <QBrush>
#include <QVector>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>

class EdgeItem;

class PortItem : public QGraphicsEllipseItem
{
public:
    explicit PortItem(Port *port, QGraphicsItem *parentNode);

    Port::Type getType() const;
    Port::Direction getDirection() const;

    QPointF sceneCenter() const;

    Port *port() const;
    QUuid portId() const;

    void addConnection(EdgeItem *edge);
    void removeConnection(EdgeItem *edge);
    const QList<EdgeItem *> &connections() const;

protected:
    void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Port *_port;
    QGraphicsLineItem *_tempLine;
    QList<EdgeItem *> _connections;
};

#endif // PORTITEM_H
