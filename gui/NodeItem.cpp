#include "NodeItem.h"

#include "../logic/node.h"
#include "portitem.h"

#include "qgraphicsscene.h"
#include "qgraphicssceneevent.h"
#include <QPainter>

NodeItem::NodeItem(Node *node) : _node(node)
{
    // Флаги для перемещения
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges
             | QGraphicsItem::ItemIsSelectable);

    // Управляющие порты
    _controlInput = new PortItem(node->controlInput(), this);
    _controlOutput = new PortItem(node->controlOutput(), this);

    _controlInput->setPos(0, 10);
    _controlOutput->setPos(160, 10);

    // DATA INPUTS
    const auto &inputs = node->inputs();
    for (int i = 0; i < inputs.size(); ++i) {
        auto *p = new PortItem(inputs[i], this);
        p->setPos(0, 40 + i * 20);
        _dataInputs.append(p);
    }

    // DATA OUTPUTS
    const auto &outputs = node->outputs();
    for (int i = 0; i < outputs.size(); ++i) {
        auto *p = new PortItem(outputs[i], this);
        p->setPos(160, 40 + i * 20);
        _dataOutputs.append(p);
    }
}

QRectF NodeItem::boundingRect() const
{
    int dataHeight = qMax(_dataInputs.size(), _dataOutputs.size()) * 20;
    return QRectF(0, 0, 160, 40 + dataHeight);
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::lightGray);
    painter->setPen(QPen(Qt::black, 1));
    painter->drawRoundedRect(boundingRect(), 5, 5);

    painter->setPen(Qt::black);
    painter->drawText(boundingRect(), Qt::AlignCenter, _node ? _node->name() : "Node");
}

PortItem *NodeItem::controlInput() const
{
    return _controlInput;
}

PortItem *NodeItem::controlOutput() const
{
    return _controlOutput;
}

Node *NodeItem::node() const
{
    return _node;
}

void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);
}

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem *clicked = scene()->itemAt(event->scenePos(), QTransform());
    if (dynamic_cast<PortItem *>(clicked)) {
        event->ignore();
        return;
    }
    QGraphicsObject::mousePressEvent(event);
}

void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseReleaseEvent(event);
}

StartNodeItem::StartNodeItem() : NodeItem(new StartNode)
{
    // ❌ нет входа управления
    delete _controlInput;
    _controlInput = nullptr;
}

const QVector<PortItem *> &NodeItem::dataInputs() const
{
    return _dataInputs;
}

const QVector<PortItem *> &NodeItem::dataOutputs() const
{
    return _dataOutputs;
}
