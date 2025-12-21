#include "connectionitem.h"
#include "portitem.h"
#include "qgraphicsscene.h"
#include "nodeitem.h"

#include <QPainter>

ConnectionItem::ConnectionItem(PortItem* from, PortItem* to)
    : m_from(from), m_to(to)
{
    setPen(QPen(Qt::black, 2));
    setZValue(-1);
    updatePath();

    from->addConnection(this);
    to->addConnection(this);
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

void ConnectionItem::disconnect()
{
    if (m_from)
        m_from->removeConnection(this);

    if (m_to)
        m_to->removeConnection(this);

    if (auto* n = m_from ? m_from->parentNodeItem() : nullptr)
        n->removeConnection(this);

    if (auto* n = m_to ? m_to->parentNodeItem() : nullptr)
        n->removeConnection(this);

    m_from = nullptr;
    m_to = nullptr;

    if (scene())
        scene()->removeItem(this);

    delete this;
}
