#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "Node.h"

class Graph
{
public:
    explicit Graph() = default;

    bool execute(NodeContext &context);

    void addNode(Node *node);
    bool addEdge(Edge *edge);

private:
    bool buildExecutionOrder(QVector<Node *> &order, QString &error);
    bool validateConnection(const Edge *edge) const;

private:
    QVector<Node *> _nodes;
    QVector<Edge *> _edges;
};

Q_DECLARE_METATYPE(Graph *)

#endif // GRAPH_H
