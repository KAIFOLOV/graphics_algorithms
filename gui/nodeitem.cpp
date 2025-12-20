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
    m_controlInput = new PortItem(PortItem::Direction::Input, this);
    m_controlOutput = new PortItem(PortItem::Direction::Output, this);

    m_controlInput->setPos(0, 10);
    m_controlOutput->setPos(140, 10);

    // Входные порты данных
    int dataInCount = 1 /*node->params().value("dataPortInCount", 0).toInt()*/;
    for (int i = 0; i < dataInCount; ++i) {
        auto inPort = new PortItem(PortItem::Direction::Input, this);
        inPort->setPos(0, 40 + i*20);
        m_dataInputs.append(inPort);
    }

    // Выходные порты данных
    int dataOutCount = 1 /*node->params().value("dataPortOutCount", 0).toInt()*/;
    for (int i = 0; i < dataOutCount; ++i) {
        auto outPort = new PortItem(PortItem::Direction::Output, this);
        outPort->setPos(140, 40 + i*20);
        m_dataOutputs.append(outPort);
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

QVector<QVariant> NodeItem::collectInputData() const
{
    QVector<QVariant> inputs;
    for (auto inPort : m_dataInputs) {
        QVariant val;
        for (auto conn : inPort->connections()) {
            NodeItem* sourceNode = conn->sourcePort()->parentNodeItem();
            int index = conn->sourcePort()->index(); // <-- здесь
            if (sourceNode)
                val = sourceNode->node()->lastOutput().value(index);
        }
        inputs.append(val);
    }
    return inputs;
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
