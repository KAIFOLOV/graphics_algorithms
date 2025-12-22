#include "nodeitem.h"
#include "connectionitem.h"
#include "../node.h"
#include "qgraphicsscene.h"
#include "qgraphicssceneevent.h"
#include <QPainter>

NodeItem::NodeItem(Node* node)
    : m_node(node)
{
    // Флаги для перемещения
    setFlags(QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemSendsGeometryChanges |
             QGraphicsItem::ItemIsSelectable);

    // Управляющие порты
    m_controlInput = new PortItem(PortItem::Direction::Input, PortItem::PortKind::Control, this);
    m_controlOutput = new PortItem(PortItem::Direction::Output, PortItem::PortKind::Control, this);

    m_controlInput->setPos(0, 10);
    m_controlOutput->setPos(160, 10);

    // DATA INPUTS
    const auto& inputs = node->inputs();
    for (int i = 0; i < inputs.size(); ++i) {
        auto* p = new PortItem(
            PortItem::Direction::Input,
            PortItem::PortKind::Data,
            this
            );

        p->setPortId(inputs[i].id());
        p->setPos(0, 40 + i * 20);
        m_dataInputs.append(p);
    }

    // DATA OUTPUTS
    const auto& outputs = node->outputs();
    for (int i = 0; i < outputs.size(); ++i) {
        auto* p = new PortItem(
            PortItem::Direction::Output,
            PortItem::PortKind::Data,
            this
            );

        p->setPortId(outputs[i].id());
        p->setPos(160, 40 + i * 20);
        m_dataOutputs.append(p);
    }
}

QRectF NodeItem::boundingRect() const
{
    int dataHeight = qMax(m_dataInputs.size(), m_dataOutputs.size()) * 20;
    return QRectF(0, 0, 160, 40 + dataHeight);
}

void NodeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setBrush(Qt::lightGray);
    painter->setPen(QPen(Qt::black, 1));
    painter->drawRoundedRect(boundingRect(), 5, 5);

    painter->setPen(Qt::black);
    painter->drawText(boundingRect(), Qt::AlignCenter, m_node ? m_node->name() : "Node");
}

Node* NodeItem::node() const
{
    return m_node;
}

void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);
    for (auto conn : m_connections)
        conn->updatePath();
}

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem* clicked = scene()->itemAt(event->scenePos(), QTransform());
    if (dynamic_cast<PortItem*>(clicked)) {
        event->ignore();
        return;
    }
    QGraphicsObject::mousePressEvent(event);
}

void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsObject::mouseReleaseEvent(event);
}

void NodeItem::removeConnection(ConnectionItem* c)
{
    m_connections.removeOne(c);
}

StartNodeItem::StartNodeItem()
    : NodeItem(new StartNode)
{
    // ❌ нет входа управления
    delete m_controlInput;
    m_controlInput = nullptr;
}
