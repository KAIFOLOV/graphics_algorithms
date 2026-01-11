#include "Graph.h"

bool Graph::execute(NodeContext &context)
{
    // StartNode *start = nullptr;

    // // ⚠️ Упрощённо: линейно
    // for (Node *n : _nodes) {
    //     if (auto *s = dynamic_cast<StartNode *>(n)) {
    //         start = s;
    //         break;
    //     }

    //     QHash<PortId, QVariant> inputs;

    //     for (auto &e : _edges)
    //         if (e.to == n)
    //             inputs[e.inPort] = e.from->lastOutput().value(e.outPort);

    //     QHash<PortId, QVariant> outputs;
    //     if (!n->execute(inputs, ctx, error, outputs))
    //         return false;
    // }
    // return true;
}

void Graph::addNode(Node *node)
{
    _nodes.push_back(node);
}

bool Graph::addEdge(Edge *edge)
{
    if (!validateConnection(edge))
        return false;

    _edges.push_back(edge);
    return true;
}

bool Graph::buildExecutionOrder(QVector<Node *> &order, QString &error)
{
    // // ищем StartNode
    // Node *start = nullptr;
    // for (Node *n : _nodes) {
    //     if (dynamic_cast<StartNode *>(n)) {
    //         start = n;
    //         break;
    //     }
    // }

    // if (!start) {
    //     error = "No Start node";
    //     return false;
    // }

    // QSet<Node *> visited;
    // Node *current = start;

    // while (current) {
    //     if (visited.contains(current)) {
    //         error = "Cycle detected";
    //         return false;
    //     }

    //     visited.insert(current);
    //     order << current;

    //     // ищем следующую по control-edge
    //     Node *next = nullptr;
    //     for (const Connection &c : _edges) {
    //         if (c.from == current && c.type == Connection::Type::Control) {
    //             next = c.to;
    //             break;
    //         }
    //     }

    //     current = next;
    // }

    // return true;
}

bool Graph::validateConnection(const Edge *edge) const
{
    if (!edge->from() || !edge->to()) {
        qWarning() << "Null node in connection";
        return false;
    }

    if (edge->from() == edge->to()) {
        qWarning() << "Self-connection is not allowed";
        return false;
    }

    return true;
}
