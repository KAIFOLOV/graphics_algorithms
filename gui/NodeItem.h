#ifndef NODEITEM_H
#define NODEITEM_H

#include "portitem.h"

#include "qpainter.h"
#include <QGraphicsObject>
#include <QVector>

class Node;

class NodeItem : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit NodeItem(Node *node);

    QRectF boundingRect() const override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

    // Управление
    PortItem *controlInput() const;
    PortItem *controlOutput() const;

    // Данные
    const QVector<PortItem *> &dataInputs() const;
    const QVector<PortItem *> &dataOutputs() const;

    Node *node() const;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;

    // Управляющие порты
    PortItem *_controlInput = nullptr;
    PortItem *_controlOutput = nullptr;

private:
    Node *_node { nullptr };

    // Порты данных
    QVector<PortItem *> _dataInputs;
    QVector<PortItem *> _dataOutputs;
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
