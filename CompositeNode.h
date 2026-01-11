#ifndef COMPOSITENODE_H
#define COMPOSITENODE_H

#include "logic/Node.h"

class CompositeNode : public Node
{
public:
    explicit CompositeNode();
    explicit CompositeNode(const QList<Node *> &nodes);

    bool execute(const QHash<QUuid, QVariant> &inputs,
                 NodeContext &ctx,
                 QHash<QUuid, QVariant> &outputs) override;

private:
    QList<Node *> _nodes;
};

#endif // COMPOSITENODE_H
