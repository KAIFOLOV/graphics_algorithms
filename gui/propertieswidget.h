#ifndef PROPERTIESWIDGET_H
#define PROPERTIESWIDGET_H

#include "../node.h"
#include <QWidget>

class PropertiesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PropertiesWidget(QWidget* parent = nullptr);

    void setNode(Node* node);

private:
    QWidget* m_editor = nullptr;
};

#endif // PROPERTIESWIDGET_H
