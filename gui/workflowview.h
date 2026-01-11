#ifndef WORKFLOWVIEW_H
#define WORKFLOWVIEW_H

#include "../logic/Graph.h"
#include "GraphItem.h"
#include "NodeItem.h"

#include <QGraphicsView>

class WorkflowView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit WorkflowView(QWidget *parent = nullptr);

    Graph *graph() const;

private:
    Graph *_graph { nullptr };
    GraphItem *_graphItem { nullptr };
};

#endif // WORKFLOWVIEW_H
