#ifndef WORKFLOWEXECUTOR_H
#define WORKFLOWEXECUTOR_H

#include "gui/nodeitem.h"
#include "node.h"
#include "qdebug.h"
#include "qgraphicsscene.h"

class WorkflowExecutor
{
public:
    void run(QGraphicsScene* scene, NodeContext& ctx);
};

#endif // WORKFLOWEXECUTOR_H
