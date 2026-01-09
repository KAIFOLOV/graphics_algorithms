#ifndef GRAPH_H
#define GRAPH_H

#include "Connection.h"
#include "node.h"

class Graph
{
public:
    bool execute(NodeContext &ctx, QString &error);

    void addNode(Node *node);
    bool addConnection(const Connection &c, QString &error);

private:
    bool buildExecutionOrder(QVector<Node *> &order, QString &error);
    bool validateConnection(const Connection &c, QString &error) const;

private:
    QVector<Node *> _nodes;
    QVector<Connection> _edges;
};
Q_DECLARE_METATYPE(Graph *)

#endif // GRAPH_H
