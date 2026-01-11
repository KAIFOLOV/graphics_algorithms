#include "CompositeNode.h"

CompositeNode::CompositeNode() : Node {}
{}

CompositeNode::CompositeNode(const QList<Node *> &nodes) : _nodes(nodes)
{}

bool CompositeNode::execute(const QHash<QUuid, QVariant> &inputs,
                            NodeContext &ctx,
                            QHash<QUuid, QVariant> &outputs)
{
    return true;
}
