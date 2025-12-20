#include "portitem.h"
#include "connectionitem.h"
#include "nodeitem.h"
#include <QGraphicsScene>

void PortItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() != Qt::LeftButton) return;
    m_tempLine = new QGraphicsLineItem(QLineF(sceneCenter(), sceneCenter()));
    scene()->addItem(m_tempLine);
    event->accept();
}

void PortItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(!m_tempLine) return;
    QLineF line(m_tempLine->line().p1(), event->scenePos());
    m_tempLine->setLine(line);
}

void PortItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (!m_tempLine)
        return;

    auto itemsAtPos = scene()->items(event->scenePos());
    for (auto* it : itemsAtPos)
    {
        auto* target = qgraphicsitem_cast<PortItem*>(it);
        if (!target)
            continue;

        if (target == this)
            continue;

        if (target->getDirection() == m_dir)
            continue;

        auto* conn = new ConnectionItem(this, target);
        scene()->addItem(conn);

        // Порты
        addConnection(conn);
        target->addConnection(conn);

        // 🔥 НОДЫ
        if (auto* n1 = parentNodeItem())
            n1->addConnection(conn);
        if (auto* n2 = target->parentNodeItem())
            n2->addConnection(conn);

        break;
    }

    scene()->removeItem(m_tempLine);
    delete m_tempLine;
    m_tempLine = nullptr;
}

NodeItem *PortItem::parentNodeItem() const
{
    return qgraphicsitem_cast<NodeItem*>(parentItem());
}
