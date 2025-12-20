#ifndef PORTITEM_H
#define PORTITEM_H

#include "qgraphicsitem.h"

class NodeItem;
class ConnectionItem;

class PortItem : public QGraphicsEllipseItem
{
public:
    enum class Type { Input, Output };

    PortItem(Type type, QGraphicsItem* parent = nullptr);

    Type getType() const { return m_type; }
    QPointF sceneCenter() const { return mapToScene(rect().center()); }

private:
    Type m_type;
};

#endif // PORTITEM_H
