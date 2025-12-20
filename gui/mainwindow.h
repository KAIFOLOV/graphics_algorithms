#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

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
    void addNode(QListWidgetItem* item);
    void selectionChanged();

private:
    // UI элементы
    QListWidget*      m_palette = nullptr;
    WorkflowView*     m_view = nullptr;
    PropertiesWidget* m_props = nullptr;

    // Контейнер для canvas + кнопка Run
    QWidget*          m_viewContainer = nullptr;

    // Прибор
    FakeVna*          m_vna = nullptr;
};

#endif // MAINWINDOW_H
