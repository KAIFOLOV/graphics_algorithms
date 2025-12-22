#ifndef COMPOSITENODE_H
#define COMPOSITENODE_H

#include "node.h"

class CompositeNode : public Node
{
public:
    explicit CompositeNode();
    explicit CompositeNode(const QList<Node *> &nodes);

    bool execute(const QHash<PortId, QVariant>& inputs,
                 NodeContext& ctx,
                 QString& error,
                 QHash<PortId, QVariant>& outputs) override;

private:
    QList<Node *> _nodes;
};

#endif // COMPOSITENODE_H
