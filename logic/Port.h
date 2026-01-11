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

    enum class Direction
    {
        Input,
        Output
    };

    explicit Port(Type type, const QString &name = "");
    explicit Port(Type type, Direction direction, const QString &name = "");

    QUuid id() const;

    Type type() const;
    void setType(Type newType);

    QString name() const;
    void setName(const QString &newName);

    Direction direction() const;
    void setDirection(Direction newDirection);

private:
    QUuid _id;
    Type _type;
    QString _name;
    Direction _direction;
};

#endif // PORT_H
