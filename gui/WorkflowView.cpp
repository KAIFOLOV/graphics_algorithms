#include "workflowview.h"

#include <QGraphicsScene>
#include <QPainter>

WorkflowView::WorkflowView(QWidget *parent) : QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);

    _graph = new Graph();
    _graphItem = new GraphItem(_graph, this);

    setScene(_graphItem);
}

Graph *WorkflowView::graph() const
{
    return _graph;
}

GraphItem *WorkflowView::graphItem() const
{
    return _graphItem;
}
