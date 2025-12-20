#include "connectionitem.h"
#include "portitem.h"

#include <QPainter>

ConnectionItem::ConnectionItem(PortItem* from, PortItem* to)
    : m_from(from), m_to(to)
{
    setPen(QPen(Qt::black, 2));
    setZValue(-1);
    updatePath();
}

void ConnectionItem::updatePath()
{
    QPointF p1 = m_from->sceneCenter();
    QPointF p2 = m_to->sceneCenter();

    QPainterPath path;
    qreal dx = (p2.x() - p1.x()) * 0.5;
    path.moveTo(p1);
    path.cubicTo(p1 + QPointF(dx, 0), p2 - QPointF(dx,0), p2);

    setPath(path);
}
