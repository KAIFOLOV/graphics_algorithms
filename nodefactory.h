#ifndef NODEFACTORY_H
#define NODEFACTORY_H

#include <QVector>
#include <functional>
#include <QMap>

class Node;

class NodeFactory
{
public:
    static NodeFactory &instance();

    void registerNode(const QString &name, std::function<Node *()> creator);

    QVector<QString> nodeNames() const;
    Node *create(const QString &name);

private:
    QMap<QString, std::function<Node *()>> m_creators;
};

#endif // NODEFACTORY_H
