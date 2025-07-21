#include "WorkspaceDockWidget.h"
#include "Viewport3DWorkspace.h"
#include "LyapunovWorkspace.h"

#include <QComboBox>
#include <QHBoxLayout>

WorkspaceDockWidget::WorkspaceDockWidget(const QString& title, QWidget* parent)
    : QDockWidget(title, parent)
{
    setAllowedAreas(Qt::AllDockWidgetAreas);
    createTitleBar();

    // —разу создаЄм контент по умолчанию
    switchTo(Type::View3D);
    m_typeCombo->setCurrentIndex(static_cast<int>(Type::View3D));
}

void WorkspaceDockWidget::createTitleBar() {
    QWidget* tb = new QWidget(this);
    auto* layout = new QHBoxLayout(tb);
    layout->setContentsMargins(2, 2, 2, 2);

    m_typeCombo = new QComboBox(tb);
    m_typeCombo->addItems({
        tr("3D Viewport"),
        tr("Lyapunov Diagram")
        // Е дополнить названи€ми новых типов
        });

    layout->addWidget(m_typeCombo);
    layout->addStretch();
    tb->setLayout(layout);
    setTitleBarWidget(tb);

    connect(m_typeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &WorkspaceDockWidget::onTypeSelected);
}

void WorkspaceDockWidget::onTypeSelected(int index) {
    Type newType = static_cast<Type>(index);
    if (newType != m_type) {
        switchTo(newType);
        emit typeChanged(newType);
    }
}

void WorkspaceDockWidget::switchTo(Type t) {
    // ”дал€ем старый виджет
    if (m_activeWidget) {
        setWidget(nullptr);
        m_activeWidget->deleteLater();
    }

    // —оздаЄм новый в зависимости от типа
    switch (t) {
    case Type::View3D: {
        m_activeWidget = new Viewport3DWorkspace(this);
        break;
    }
    case Type::Lyapunov: {
        m_activeWidget = new LyapunovWorkspace(this);
        break;
    }
                       // Е другие типы
    }

    m_type = t;
    setWidget(m_activeWidget);
}
