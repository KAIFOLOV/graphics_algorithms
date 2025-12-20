#include "nodeitem.h"
#include "../node.h"
#include "connectionitem.h"
#include <QPainter>

NodeItem::NodeItem(Node* node)
    : QGraphicsObject(nullptr)
    , m_node(node)
{
    setFlags(ItemIsMovable | ItemIsSelectable);

    // создаем порты
    m_input = new PortItem(PortItem::Type::Input, this);
    m_output = new PortItem(PortItem::Type::Output, this);

    // позиционируем порты по центру левой и правой стороны
    m_input->setPos(0, boundingRect().height()/2);
    m_output->setPos(boundingRect().width(), boundingRect().height()/2);
}

QRectF NodeItem::boundingRect() const
{
    return QRectF(0, 0, 180, 50);
}

void NodeItem::paint(QPainter* p,
                     const QStyleOptionGraphicsItem*,
                     QWidget*)
{
    p->setRenderHint(QPainter::Antialiasing);

    // фон
    QColor bg = Qt::lightGray;
    p->setBrush(bg);
    p->setPen(QPen(Qt::black, 1));
    p->drawRoundedRect(boundingRect(), 5, 5);

    // текст
    p->setPen(Qt::black);
    p->drawText(boundingRect(), Qt::AlignCenter, m_node ? m_node->name() : "Node");
}

Node* NodeItem::node() const
{
    return m_node;
}

void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsObject::mouseMoveEvent(event);

    // обновляем все соединения, чтобы линии двигались за нодой
    for (auto* conn : m_connections)
        conn->updatePath();
}
