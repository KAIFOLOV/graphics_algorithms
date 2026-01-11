#include "mainwindow.h"
#include "NodeItem.h"
#include "propertieswidget.h"
#include "workflowview.h"
#include "../workflowexecutor.h"
#include "../nodefactory.h"
#include "../IVna.h"
#include "EdgeItem.h"

#include <QSplitter>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QWidget>
#include <QToolBar>

MainWindow::MainWindow()
{
    // Создаём прибор (FakeVna для теста)
    _vna = new FakeVna;

    // Левая панель — палитра нод
    _palette = new QListWidget;
    for (auto &node : NodeFactory::instance().nodeNames()) {
        _palette->addItem(node);
    }

    // Центральная панель — canvas
    _view = new WorkflowView;

    // Правая панель — свойства выбранной ноды
    _props = new PropertiesWidget;

    // Основной сплиттер
    auto *splitter = new QSplitter;
    splitter->addWidget(_palette);
    splitter->addWidget(_view);
    splitter->addWidget(_props);
    splitter->setStretchFactor(1, 1); // canvas растягивается

    setCentralWidget(splitter);

    // Кнопка запуска workflow — добавляем в toolbar
    auto *toolbar = addToolBar("Workflow");

    auto *runBtn = new QPushButton("Run");
    toolbar->addWidget(runBtn);

    auto *saveBtn = new QPushButton("Save");
    toolbar->addWidget(saveBtn);

    connect(runBtn, &QPushButton::clicked, this, [this]() {
        NodeContext ctx;
        ctx.set(_vna);

        WorkflowExecutor exec;
        exec.run(*_view->graph(), ctx);
    });

    connect(saveBtn, &QPushButton::clicked, this, [this]() {});

    // Подключаем добавление ноды при двойном клике на палитре
    connect(_palette, &QListWidget::itemDoubleClicked, this, &MainWindow::addNode);

    // Подключаем отображение свойств при выборе ноды
    connect(_view->scene(), &QGraphicsScene::selectionChanged, this, &MainWindow::selectionChanged);
}

void MainWindow::addNode(QListWidgetItem *item)
{
    auto *node = NodeFactory::instance().create(item->text());
    if (!node)
        return;

    _view->graph()->addNode(node);

    auto *ni = new NodeItem(node);
    _view->scene()->addItem(ni);
    ni->setPos(50, 50);
}

void MainWindow::selectionChanged()
{
    auto items = _view->scene()->selectedItems();
    if (items.isEmpty())
        return;

    auto *ni = dynamic_cast<NodeItem *>(items.first());
    if (ni)
        _props->setNode(ni->node());
}
