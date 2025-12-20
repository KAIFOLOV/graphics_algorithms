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
                        [](const QVariantMap&, NodeContext& ctx, QString&) {
                            return ctx.vna->connect();
                        });
    });

    f.registerNode("Set Start Frequency", [] {
        auto* n = new Node("Set Start Frequency",
                           [](const QVariantMap& p, NodeContext& ctx, QString&) {
                               return ctx.vna->setStartFrequency(p["freq"].toDouble());
                           });
        n->params()["freq"] = 1e9;
        return n;
    });

    f.registerNode("Set Stop Frequency", [] {
        auto* n = new Node("Set Stop Frequency",
                           [](const QVariantMap& p, NodeContext& ctx, QString&) {
                               return ctx.vna->setStopFrequency(p["freq"].toDouble());
                           });
        n->params()["freq"] = 10e9;
        return n;
    });

    f.registerNode("Set Points", [] {
        auto* n = new Node("Set Points",
                           [](const QVariantMap& p, NodeContext& ctx, QString&) {
                               return ctx.vna->setPoints(p["pts"].toInt());
                           });
        n->params()["pts"] = 201;
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
