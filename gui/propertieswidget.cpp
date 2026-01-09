#include "propertieswidget.h"

#include <QFormLayout>
#include <QDoubleSpinBox>
#include <QSpinBox>

PropertiesWidget::PropertiesWidget(QWidget *parent) : QWidget(parent)
{
    setLayout(new QVBoxLayout);
}

void PropertiesWidget::setNode(Node *node)
{
    if (m_editor)
        m_editor->deleteLater();

    auto *w = new QWidget;
    auto *l = new QFormLayout(w);

    for (auto it = node->params().begin(); it != node->params().end(); ++it) {
        if (it.value().type() == QVariant::Double) {
            auto *s = new QDoubleSpinBox;
            s->setValue(it.value().toDouble());
            connect(s, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
                    [node, key = it.key()](double v) {
                        node->params()[key] = v;
                    });
            l->addRow(it.key(), s);
        }
        if (it.value().type() == QVariant::Int) {
            auto *s = new QSpinBox;
            s->setValue(it.value().toInt());
            connect(s, QOverload<int>::of(&QSpinBox::valueChanged), this,
                    [node, key = it.key()](int v) {
                        node->params()[key] = v;
                    });
            l->addRow(it.key(), s);
        }
    }

    layout()->addWidget(w);
    m_editor = w;
}
