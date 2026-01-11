#include "workflowexecutor.h"

#include <QDebug>

void WorkflowExecutor::run(Graph &graph, NodeContext &ctx)
{
    graph.execute(ctx);
}
