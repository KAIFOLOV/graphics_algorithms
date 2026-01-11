#include "GraphItem.h"

GraphItem::GraphItem(Graph *graph, QObject *parent) : QGraphicsScene { parent }, _graph(graph)
{
    auto startNode = new StartNodeItem();
    addItem(startNode);
    startNode->setPos(30, 100);
}

void GraphItem::addNodeItem(Node *node, const QPointF &pos)
{}

void GraphItem::removeNodeItem(NodeItem *item)
{}

void GraphItem::createEdge(PortItem *from, PortItem *to)
{
    // --- 1. Типы портов должны совпадать ---
    if (from->getType() != to->getType())
        return;

    // --- 2. Направление должно быть противоположным ---
    if (from->getDirection() == to->getDirection())
        return;

    // --- Нормализуем порядок: from = Output, to = Input ---
    PortItem *src = (from->getDirection() == Port::Direction::Output) ? from : to;
    PortItem *dst = (src == from ? to : from);

    // --- 3. Проверка: такое соединение уже существует ---
    for (auto *edgeItem : _edges) {
        if (edgeItem->fromPort() == src && edgeItem->toPort() == dst) {
            qDebug() << "Edge already exists";
            return;
        }
    }

    // --- 4. Проверка: управляющие порты имеют только 1 соединение ---
    if (src->getType() == Port::Type::Control) {
        // У Output Control может быть только один выход
        if (!src->connections().isEmpty()) {
            qDebug() << "Control output already connected";
            return;
        }
    }

    if (dst->getType() == Port::Type::Control) {
        // У Input Control может быть только один вход
        if (!dst->connections().isEmpty()) {
            qDebug() << "Control input already connected";
            return;
        }
    }

    // Логическое соединение
    auto *edge = new Edge(from->port(), to->port());

    // UI-соединение
    auto *item = new EdgeItem(edge, from, to);
    addItem(item);
    _edges.append(item);

    src->addConnection(item);
    dst->addConnection(item);
}

void GraphItem::removeEdge(EdgeItem *edge)
{
    if (!edge)
        return;

    edge->fromPort()->removeConnection(edge);
    edge->toPort()->removeConnection(edge);

    _edges.removeOne(edge);
    removeItem(edge);
    delete edge;
}
