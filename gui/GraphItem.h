#ifndef GRAPHITEM_H
#define GRAPHITEM_H

#include "EdgeItem.h"
#include "NodeItem.h"
#include "../logic/Graph.h"

#include <QGraphicsScene>

class GraphItem : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GraphItem(Graph *graph, QObject *parent = nullptr);

    void addNodeItem(Node *node, const QPointF &pos);
    void removeNodeItem(NodeItem *item);

    void createEdge(PortItem *from, PortItem *to);
    void removeEdge(EdgeItem *edge);

private:
    Graph *_graph;
    QVector<EdgeItem *> _edges;
    QVector<NodeItem *> _nodeItems;
};

#endif // GRAPHITEM_H
