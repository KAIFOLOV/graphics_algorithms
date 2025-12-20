#include "workflowexecutor.h"
#include "gui/connectionitem.h"

#include <QQueue>
#include <QDebug>

void WorkflowExecutor::run(QGraphicsScene *scene, NodeContext &ctx)
{
    QList<NodeItem*> nodes;
    for (auto* item : scene->items())
        if (auto* ni = dynamic_cast<NodeItem*>(item))
            nodes.append(ni);

    QString err;
    for (auto* ni : nodes) {
        QVector<QVariant> inputs = ni->collectInputData(); // собираем данные с входных портов
        QVector<QVariant> outputs;

        if (!ni->node()->execute(inputs, ctx, err, outputs)) {
            qWarning() << "Error executing" << ni->node()->name() << ":" << err;
            break;
        }

        // outputs автоматически сохраняются в Node::lastOutput
        Q_UNUSED(outputs);
    }
}
