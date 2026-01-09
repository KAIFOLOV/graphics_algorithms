#ifndef WORKFLOWEXECUTOR_H
#define WORKFLOWEXECUTOR_H

#include "Graph.h"

class WorkflowExecutor
{
public:
    void run(Graph &graph, NodeContext &ctx);
};

#endif // WORKFLOWEXECUTOR_H
