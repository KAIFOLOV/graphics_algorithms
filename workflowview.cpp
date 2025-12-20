#include "workflowview.h"
#include "gui/connectionitem.h"
#include "gui/nodeitem.h"

#include <QGraphicsScene>
#include <QPainter>

WorkflowView::WorkflowView(QWidget* parent)
    : QGraphicsView(parent)
{
    setScene(new QGraphicsScene(this));
    setRenderHint(QPainter::Antialiasing);
}

void WorkflowView::createConnection(NodeItem* from, NodeItem* to)
{
    // auto* conn = new ConnectionItem(from->outputPort(), to->inputPort());
    // scene()->addItem(conn);
}
