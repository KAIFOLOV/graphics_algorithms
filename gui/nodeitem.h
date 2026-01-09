#ifndef NODEITEM_H
#define NODEITEM_H

#include "portitem.h"
#include "qpainter.h"
#include <QGraphicsObject>
#include <QVector>

class Node;
class ConnectionItem;

class NodeItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit NodeItem(Node *node);

    QRectF boundingRect() const override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

    // Управление
    PortItem *controlInput() const
    {
        return m_controlInput;
    }
    PortItem *controlOutput() const
    {
        return m_controlOutput;
    }

    // Данные
    const QVector<PortItem *> &dataInputs() const
    {
        return m_dataInputs;
    }
    const QVector<PortItem *> &dataOutputs() const
    {
        return m_dataOutputs;
    }

    Node *node() const;

    void addConnection(ConnectionItem *conn)
    {
        m_connections.append(conn);
    }
    const QVector<ConnectionItem *> &connections() const
    {
        return m_connections;
    }

    // собрать данные с входных портов
    // QVector<QVariant> collectInputData() const;

    void removeConnection(ConnectionItem *c);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    // Управляющие порты
    PortItem *m_controlInput = nullptr;
    PortItem *m_controlOutput = nullptr;

private:
    Node *m_node = nullptr;

    // Порты данных
    QVector<PortItem *> m_dataInputs;
    QVector<PortItem *> m_dataOutputs;

    QVector<ConnectionItem *> m_connections;
};

class StartNodeItem : public NodeItem
{
public:
    StartNodeItem();

    QRectF boundingRect() const override
    {
        return QRectF(0, 0, 160, 40);
    }

    void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *) override
    {
        p->setBrush(QColor(120, 200, 120));
        p->setPen(Qt::black);
        p->drawRoundedRect(boundingRect(), 10, 10);
        p->drawText(boundingRect(), Qt::AlignCenter, "START");
    }
};

#endif // NODEITEM_H
