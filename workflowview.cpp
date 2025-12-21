#include "workflowview.h"
#include "gui/connectionitem.h"
#include "gui/nodeitem.h"

#include <QGraphicsScene>
#include <QPainter>

WorkflowView::WorkflowView(QWidget* parent)
    : QGraphicsView(parent)
{
    m_scene = new QGraphicsScene(this);
    setScene(m_scene);

    // 🔴 СОЗДАЁМ START-АВТОМАТИЧЕСКИ
    m_startNode = new StartNodeItem;
    m_scene->addItem(m_startNode);
    m_startNode->setPos(30, 100);

    setRenderHint(QPainter::Antialiasing);
}
