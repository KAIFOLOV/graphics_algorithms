#include "workflowexecutor.h"
#include "gui/connectionitem.h"

#include <QQueue>
#include <QDebug>

static NodeItem* nextByControl(NodeItem* node)
{
    auto* out = node->controlOutput();
    if (!out || out->connections().isEmpty())
        return nullptr;

    auto* conn = out->connections().first();
    return conn->targetPort()->parentNodeItem();
}

void WorkflowExecutor::run(QGraphicsScene* scene, NodeContext& ctx)
{
    StartNodeItem* start = nullptr;

    for (auto* it : scene->items()) {
        if (auto* s = dynamic_cast<StartNodeItem*>(it)) {
            start = s;
            break;
        }
    }

    if (!start) {
        qWarning() << "No Start node";
        return;
    }

    QSet<NodeItem*> visited;
    NodeItem* current = start;

    QString err;

    while (current) {
        if (visited.contains(current)) {
            qWarning() << "Cycle detected";
            break;
        }
        visited.insert(current);

        QVector<QVariant> inputs = current->collectInputData();
        QVector<QVariant> outputs;

        if (current->node()) {
            if (!current->node()->execute(inputs, ctx, err, outputs)) {
                qWarning() << "Execution error:" << err;
                break;
            }
        }

        current = nextByControl(current);
    }
}
