#include "IVna.h"
#include "gui/mainwindow.h"
#include "node.h"
#include "nodefactory.h"

#include <QApplication>

void registerVnaNodes()
{
    auto& f = NodeFactory::instance();

    f.registerNode("VNA Connect", [] {
        return new Node("VNA Connect",
                        [](const QVariantMap&, const QVector<QVariant>&, NodeContext& ctx, QString&, QVector<QVariant>&) -> bool {
                            return ctx.vna->connect();
                        });
    });

    f.registerNode("Set Start Frequency", [] {
        auto* n = new Node("Set Start Frequency",
                           [](const QVariantMap& p, const QVector<QVariant>&, NodeContext& ctx, QString&, QVector<QVariant>&) -> bool {
                               return ctx.vna->setStartFrequency(p["freq"].toDouble());
                           });
        n->params()["freq"] = 1e9;
        return n;
    });

    f.registerNode("Set Stop Frequency", [] {
        auto* n = new Node("Set Stop Frequency",
                           [](const QVariantMap& p, const QVector<QVariant>&, NodeContext& ctx, QString&, QVector<QVariant>&) -> bool {
                               return ctx.vna->setStopFrequency(p["freq"].toDouble());
                           });
        n->params()["freq"] = 10e9;
        return n;
    });

    f.registerNode("Set Points", [] {
        auto* n = new Node("Set Points",
                           [](const QVariantMap& p, const QVector<QVariant>&, NodeContext& ctx, QString&, QVector<QVariant>&) -> bool {
                               return ctx.vna->setPoints(p["pts"].toInt());
                           });
        n->params()["pts"] = 201;
        return n;
    });

    f.registerNode("Get number", [] {
        auto* n = new Node("Get number",
                           [](const QVariantMap&, const QVector<QVariant>&, NodeContext& ctx, QString&, QVector<QVariant>& outputs) -> bool {
                               int number = ctx.vna->getNumber();
                               outputs = { number }; // кладём в выходной порт
                               return true;
                           });
        n->params()["dataPortCount"] = 1;
        return n;
    });

    f.registerNode("Print number", [] {
        auto* n = new Node("Print number",
                           [](const QVariantMap& p,
                              const QVector<QVariant>& inputs,
                              NodeContext& ctx,
                              QString&,
                              QVector<QVariant>& outputs) -> bool
                           {
                               if (inputs.isEmpty()) return false;

                               int number = inputs[0].toInt();
                               ctx.vna->printNumber(number);

                               outputs = inputs; // если нужно передать дальше
                               return true;
                           });

        n->params()["dataPortCount"] = 1; // один вход и один выход данных
        return n;
    });
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    registerVnaNodes();

    MainWindow w;
    w.resize(1000, 600);
    w.show();

    return a.exec();
}
