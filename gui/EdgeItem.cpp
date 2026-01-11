#include "EdgeItem.h"

#include <QPainter>
#include "qgraphicsscene.h"

EdgeItem::EdgeItem(Edge *edge, PortItem *from, PortItem *to) : _edge(edge), _from(from), _to(to)
{
    setPen(QPen(Qt::black, 2));
    setZValue(-1);
    updatePath();
}

void EdgeItem::updatePath()
{
    if (!_from || !_to)
        return;

    QPointF p1 = _from->sceneCenter();
    QPointF p2 = _to->sceneCenter();

    QPainterPath path;
    qreal dx = (p2.x() - p1.x()) * 0.5;
    path.moveTo(p1);
    path.cubicTo(p1 + QPointF(dx, 0), p2 - QPointF(dx, 0), p2);

    setPath(path);
}

Edge *EdgeItem::edge() const
{
    return _edge;
}

PortItem *EdgeItem::fromPort() const
{
    return _from;
}

PortItem *EdgeItem::toPort() const
{
    return _to;
}
