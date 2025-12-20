#include "mainwindow.h"
#include "nodeitem.h"
#include "propertieswidget.h"
#include "../workflowview.h"
#include "../workflowexecutor.h"
#include "../nodefactory.h"
#include "../IVna.h"

#include <QSplitter>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QWidget>
#include <QToolBar>

MainWindow::MainWindow()
{
    // Создаём прибор (FakeVna для теста)
    m_vna = new FakeVna;

    // Левая панель — палитра нод
    m_palette = new QListWidget;
    for (auto& n : NodeFactory::instance().nodeNames())
        m_palette->addItem(n);

    // Центральная панель — canvas
    m_view = new WorkflowView;

    // Правая панель — свойства выбранной ноды
    m_props = new PropertiesWidget;

    // Основной сплиттер
    auto* splitter = new QSplitter;
    splitter->addWidget(m_palette);
    splitter->addWidget(m_view);
    splitter->addWidget(m_props);
    splitter->setStretchFactor(1, 1); // canvas растягивается

    setCentralWidget(splitter);

    // Кнопка запуска workflow — добавляем в toolbar
    auto* toolbar = addToolBar("Workflow");
    auto* runBtn = new QPushButton("Run");
    toolbar->addWidget(runBtn);

    connect(runBtn, &QPushButton::clicked, this, [this]() {
        NodeContext ctx;
        ctx.vna = m_vna;

        WorkflowExecutor exec;
        exec.run(m_view->scene(), ctx);
    });

    // Подключаем добавление ноды при двойном клике на палитре
    connect(m_palette, &QListWidget::itemDoubleClicked,
            this, &MainWindow::addNode);

    // Подключаем отображение свойств при выборе ноды
    connect(m_view->scene(), &QGraphicsScene::selectionChanged,
            this, &MainWindow::selectionChanged);

    Node* getNumber = new Node("Get number",
                               [](const QVariantMap&, const QVector<QVariant>&, NodeContext& ctx, QString&, QVector<QVariant>& outputs) -> bool {
                                   int number = ctx.vna->getNumber();
                                   outputs = { number }; // кладём в выходной порт
                                   return true;
                               });

    Node* printNumber = new Node("Print number",
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

    // создаем NodeItem
    NodeItem* ni1 = new NodeItem(getNumber);
    NodeItem* ni2 = new NodeItem(printNumber);
    m_view->scene()->addItem(ni1);
    m_view->scene()->addItem(ni2);
}

void MainWindow::addNode(QListWidgetItem* item)
{
    auto* node = NodeFactory::instance().create(item->text());
    if (!node)
        return;

    auto* ni = new NodeItem(node);
    m_view->scene()->addItem(ni);
    ni->setPos(50, 50);
}

void MainWindow::selectionChanged()
{
    auto items = m_view->scene()->selectedItems();
    if (items.isEmpty())
        return;

    auto* ni = dynamic_cast<NodeItem*>(items.first());
    if (ni)
        m_props->setNode(ni->node());
}
