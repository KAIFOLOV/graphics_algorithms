#include "workflowexecutor.h"

#include "Graph.h"

#include <QDebug>

void WorkflowExecutor::run(Graph& graph, NodeContext& ctx)
{
    QString error;
    if (!graph.execute(ctx, error)) {
        qWarning() << "Execution failed:" << error;
    }
}
