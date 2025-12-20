#ifndef NODEITEM_H
#define NODEITEM_H

#include "portitem.h"
#include <QGraphicsObject>
#include <QVector>

class Node;
class ConnectionItem;

class NodeItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit NodeItem(Node* node);

    QRectF boundingRect() const override;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

    // Управление
    PortItem* controlInput() const { return m_controlInput; }
    PortItem* controlOutput() const { return m_controlOutput; }

    // Данные
    const QVector<PortItem*>& dataInputs() const { return m_dataInputs; }
    const QVector<PortItem*>& dataOutputs() const { return m_dataOutputs; }

    Node* node() const;

    void addConnection(ConnectionItem* conn) { m_connections.append(conn); }
    const QVector<ConnectionItem*>& connections() const { return m_connections; }

    // собрать данные с входных портов
    QVector<QVariant> collectInputData() const;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Node* m_node = nullptr;

    // Управляющие порты
    PortItem* m_controlInput = nullptr;
    PortItem* m_controlOutput = nullptr;

    // Порты данных
    QVector<PortItem*> m_dataInputs;
    QVector<PortItem*> m_dataOutputs;

    QVector<ConnectionItem*> m_connections;
};

#endif // NODEITEM_H
