#ifndef NODEPORT_H
#define NODEPORT_H

#include <QUuid>

using PortId = QUuid;

class NodePort
{
public:
    NodePort(const QString &name);

    PortId id() const;

private:
    QString _name;
    PortId _id;
};

#endif // NODEPORT_H
