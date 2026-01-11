#include "GraphItem.h"

GraphItem::GraphItem(Graph *graph, QObject *parent) : QGraphicsScene { parent }, _graph(graph)
{
    auto startNode = new StartNodeItem();
    addItem(startNode);
    startNode->setPos(30, 100);
}

NodeItem *GraphItem::addNodeItem(Node *node, const QPointF &pos)
{}

void GraphItem::removeNodeItem(NodeItem *item)
{}

EdgeItem *GraphItem::createEdge(PortItem *from, PortItem *to)
{}

void GraphItem::removeEdge(EdgeItem *edge)
{}
