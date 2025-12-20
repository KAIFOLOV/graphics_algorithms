#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QVariantMap>
#include <functional>

class IVna;

struct NodeContext
{
    IVna* vna = nullptr;
};

class Node : public QObject
{
    Q_OBJECT
public:
    using Callback =
        std::function<bool(const QVariantMap&, NodeContext&, QString&)>;

    explicit Node(const QString& name,
                  Callback cb,
                  QObject* parent = nullptr);

    QString name() const;

    QVariantMap& params();

    bool execute(NodeContext& ctx, QString& error);

signals:
    void updated();

private:
    QString     m_name;
    QVariantMap m_params;
    Callback    m_cb;
};

#endif // NODE_H
