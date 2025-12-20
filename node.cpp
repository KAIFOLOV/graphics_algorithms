#include "node.h"

Node::Node(const QString& name, Callback cb, QObject* parent)
    : QObject(parent), m_name(name), m_cb(cb)
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

bool Node::execute(const QVector<QVariant>& inputs, NodeContext& ctx, QString& error, QVector<QVariant>& outputs)
{
    if (!m_cb) {
        error = "No callback";
        return false;
    }

    bool ok = m_cb(m_params, inputs, ctx, error, outputs);
    if (ok)
        m_lastOutput = outputs;

    return ok;
}
