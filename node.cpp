#include "node.h"

Node::Node(const QString& name, Callback cb, QObject* parent)
    : QObject(parent)
    , m_name(name)
    , m_cb(cb)
{
}

QString Node::name() const
{
    return m_name;
}

QVariantMap& Node::params()
{
    return m_params;
}

bool Node::execute(NodeContext& ctx, QString& error)
{
    if (!m_cb) {
        error = "No callback";
        return false;
    }
    return m_cb(m_params, ctx, error);
}
