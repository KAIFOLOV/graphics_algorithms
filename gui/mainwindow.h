#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "../IVna.h"

class QListWidget;
class WorkflowView;
class PropertiesWidget;
class NodeItem;

// для теста прибор
class FakeVna;
struct NodeContext;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void addNode(QListWidgetItem *item);
    void selectionChanged();

private:
    // Палетка с нодами
    QListWidget *_palette { nullptr };
    // Рабочая область редактора
    WorkflowView *_view { nullptr };
    // Окно с параметрами функции (аргументы которые не через вход)
    PropertiesWidget *_props { nullptr };

    // Контейнер для canvas + кнопка Run
    QWidget *_viewContainer { nullptr };

    // Прибор
    IVna *_vna { nullptr };
};

#endif // MAINWINDOW_H
