#include "CompositeNode.h"

CompositeNode::CompositeNode()
    : Node{}
{}

CompositeNode::CompositeNode(const QList<Node *> &nodes) : _nodes(nodes)
{}

bool CompositeNode::execute(const QHash<PortId, QVariant>& inputs,
                            NodeContext& ctx,
                            QString& error,
                            QHash<PortId, QVariant>& outputs)
{
    return true;
}
