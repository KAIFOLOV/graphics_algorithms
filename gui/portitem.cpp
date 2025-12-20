#include "portitem.h"
#include "connectionitem.h"

#include "nodeitem.h"

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

NodeItem *PortItem::parentNodeItem() const { return static_cast<NodeItem*>(parentItem()); }
