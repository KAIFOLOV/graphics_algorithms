#ifndef WORKFLOWVIEW_H
#define WORKFLOWVIEW_H

#include "Graph.h"
#include "gui/nodeitem.h"
#include <QGraphicsView>

class WorkflowView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit WorkflowView(QWidget *parent = nullptr);

    StartNodeItem *startNode() const
    {
        return m_startNode;
    }

    Graph *graph() const;

private:
    Graph *_graph;
    QGraphicsScene *m_scene;
    StartNodeItem *m_startNode = nullptr;
};

#endif // WORKFLOWVIEW_H
