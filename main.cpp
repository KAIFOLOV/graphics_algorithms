#include "IVna.h"
#include "gui/mainwindow.h"
#include "logic/Node.h"
#include "nodefactory.h"
#include "MethodNodeFactoryHybrid.h"

#include <QApplication>

void registerVnaNodes()
{
    auto &f = NodeFactory::instance();

    // Подключение
    f.registerNode("VNA Connect", []() -> Node * {
        return new Node("VNA Connect",
                        MethodNodeFactoryHybrid<decltype(&IVna::connect)>::make(&IVna::connect));
    });

    // Установка стартовой частоты
    f.registerNode("Set Start Frequency", []() -> Node * {
        auto *n = new Node("Set Start Frequency",
                           MethodNodeFactoryHybrid<decltype(&IVna::setStartFrequency)>::make(
                            &IVna::setStartFrequency));
        n->params()["startFreq"] = 1e9; // GUI параметр по умолчанию
        return n;
    });

    // Установка стоповой частоты
    f.registerNode("Set Stop Frequency", []() -> Node * {
        auto *n = new Node(
         "Set Stop Frequency",
         MethodNodeFactoryHybrid<decltype(&IVna::setStopFrequency)>::make(&IVna::setStopFrequency));
        n->params()["stopFreq"] = 10e9;
        return n;
    });

    // Количество точек
    f.registerNode("Set Points", []() -> Node * {
        auto *n = new Node(
         "Set Points", MethodNodeFactoryHybrid<decltype(&IVna::setPoints)>::make(&IVna::setPoints));
        n->params()["countPoints"] = 201;
        return n;
    });

    // Получение числа
    f.registerNode("Get Number", []() -> Node * {
        auto node = new Node(
         "Get Number", MethodNodeFactoryHybrid<decltype(&IVna::getNumber)>::make(&IVna::getNumber));
        node->addOutput(new Port(Port::Type::Data, "Number"));
        return node;
    });

    // Печать числа
    f.registerNode("Print Number", []() -> Node * {
        auto *node =
         new Node("Print Number",
                  MethodNodeFactoryHybrid<decltype(&IVna::printNumber)>::make(&IVna::printNumber));
        node->addInput(new Port(Port::Type::Data, "Number"));
        return node;
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
