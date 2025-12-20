#include "nodefactory.h"

#include "Node.h"
#include "IVna.h"

NodeFactory& NodeFactory::instance()
{
    static NodeFactory f;
    return f;
}

void NodeFactory::registerNode(const QString& name,
                               std::function<Node*()> creator)
{
    m_creators[name] = creator;
}

QVector<QString> NodeFactory::nodeNames() const
{
    return m_creators.keys().toVector();
}

Node* NodeFactory::create(const QString& name)
{
    return m_creators.value(name)();
}
