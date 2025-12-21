#include "portitem.h"
#include "connectionitem.h"
#include "nodeitem.h"
#include "qpainter.h"
#include <QGraphicsScene>

void PortItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() != Qt::LeftButton)
        return;

    // 🔥 если есть соединение — рвём его
    if (!m_connections.isEmpty()) {
        auto* conn = m_connections.first();
        conn->disconnect();
    }

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

        if (target->kind() != kind())
            continue; // data нельзя соединять с control

        if (target->getDirection() == getDirection())
            continue; // input-input / output-output нельзя

        if (!this->canAcceptConnection())
            break;

        if (!target->canAcceptConnection())
            break;

        auto* conn = new ConnectionItem(this, target);
        scene()->addItem(conn);

        // Порты
        // addConnection(conn);
        // target->addConnection(conn);

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

void PortItem::addConnection(ConnectionItem *conn) {
    m_connections.append(conn);
}

NodeItem *PortItem::parentNodeItem() const
{
    return qgraphicsitem_cast<NodeItem*>(parentItem());
}

void PortItem::paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*)
{
    QColor color;
    if (m_kind == PortKind::Control)
        color = (m_dir == Direction::Input) ? QColor(180, 80, 80) : QColor(220, 50, 50);
    else
        color = (m_dir == Direction::Input) ? QColor(80, 80, 180) : QColor(50, 180, 50);

    p->setBrush(color);
    p->setPen(Qt::black);
    p->drawEllipse(boundingRect());
}

bool PortItem::canAcceptConnection() const
{
    // 🔴 Главное правило
    if (m_kind == PortKind::Control &&
        m_dir == Direction::Output &&
        !m_connections.isEmpty())
        return false;

    return true;
}

void PortItem::removeConnection(ConnectionItem* c)
{
    m_connections.removeOne(c);
}
