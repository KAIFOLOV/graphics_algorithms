#ifndef PORT_H
#define PORT_H

#include <QUuid>

class Port
{
public:
    enum class Type
    {
        Data,
        Control
    };

    Port(Type type, const QString &name = "");

    QUuid id() const;

    Type type() const;
    void setType(Type newType);

    QString name() const;
    void setName(const QString &newName);

private:
    QUuid _id;
    Type _type;
    QString _name;
};

#endif // PORT_H
