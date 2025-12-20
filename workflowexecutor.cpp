#include "workflowexecutor.h"
#include "gui/connectionitem.h"

#include <QQueue>

void WorkflowExecutor::run(QGraphicsScene *scene, NodeContext &ctx)
{
    QList<NodeItem*> nodes;
    for (auto* item : scene->items())
        if (auto* ni = dynamic_cast<NodeItem*>(item))
            nodes.append(ni);

    QString err;
    for (auto* ni : nodes) {
        if (!ni->node()->execute(ctx, err)) {
            qWarning() << "Error executing" << ni->node()->name() << ":" << err;
            break;
        }
    }
}
