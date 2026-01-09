#include "portitem.h"
#include "connectionitem.h"
#include "nodeitem.h"
#include "qpainter.h"
#include <QGraphicsScene>

#include "../Graph.h"

static Graph *graphFromScene(QGraphicsScene *scene)
{
    if (!scene)
        return nullptr;

    QVariant v = scene->property("graph");
    if (!v.isValid())
        return nullptr;

    return v.value<Graph *>();
}

void PortItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    // 🔥 если есть соединение — рвём его
    if (!m_connections.isEmpty()) {
        auto *conn = m_connections.first();
        conn->disconnect();
    }

    m_tempLine = new QGraphicsLineItem(QLineF(sceneCenter(), sceneCenter()));
    scene()->addItem(m_tempLine);
    event->accept();
}

void PortItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!m_tempLine)
        return;

    QLineF line(m_tempLine->line().p1(), event->scenePos());
    m_tempLine->setLine(line);
}

void PortItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (!m_tempLine)
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

    // временная линия будет удалена в любом случае
    QGraphicsLineItem *tempLine = m_tempLine;
    m_tempLine = nullptr;
    scene()->removeItem(tempLine);
    delete tempLine;

    // нет цели — выходим
    if (!target)
        return;

    // проверка направления и типа порта
    if (target->kind() != kind() || target->getDirection() == getDirection())
        return;

    // проверка возможности соединения
    if (!canAcceptConnection() || !target->canAcceptConnection())
        return;

    // получаем граф
    Graph *graph = graphFromScene(scene());
    if (!graph)
        return;

    NodeItem *fromItem = parentNodeItem();
    NodeItem *toItem = target->parentNodeItem();
    if (!fromItem || !toItem)
        return;

    // создаем логическое соединение
    Connection model;
    model.from = fromItem->node();
    model.to = toItem->node();
    model.outPort = m_portId;
    model.inPort = target->portId();
    model.type = (kind() == PortKind::Control) ? Connection::Type::Control : Connection::Type::Data;

    QString error;
    if (!graph->addConnection(model, error)) {
        qWarning() << "Connection rejected:" << error;
        return;
    }

    // создаем GUI-соединение
    auto *item = new ConnectionItem(model, this, target);
    scene()->addItem(item);

    fromItem->addConnection(item);
    toItem->addConnection(item);
}

void PortItem::addConnection(ConnectionItem *conn)
{
    if (!m_connections.contains(conn))
        m_connections.append(conn);
}

NodeItem *PortItem::parentNodeItem() const
{
    return qgraphicsitem_cast<NodeItem *>(parentItem());
}

void PortItem::paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *)
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
    if (m_kind == PortKind::Control && m_dir == Direction::Output && !m_connections.isEmpty())
        return false;

    return true;
}

void PortItem::removeConnection(ConnectionItem *c)
{
    m_connections.removeOne(c);
}
