#include "portitem.h"
#include "connectionitem.h"

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

PortItem::PortItem(Type type, QGraphicsItem* parent)
    : QGraphicsEllipseItem(parent)
    , m_type(type)
{
    setRect(-5, -5, 10, 10);
    setBrush(type == Type::Input ? Qt::blue : Qt::green);
}
