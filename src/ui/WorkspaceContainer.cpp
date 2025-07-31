#include "ui/WorkspaceContainer.h"

#include <QComboBox>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QMetaObject>  

namespace ODV {

    WorkspaceContainer::WorkspaceContainer(QWidget* parent)
        : QWidget(parent)
        , m_typeCombo(new QComboBox(this))
        , m_stack(new QStackedWidget(this))
        , m_ws3d(new Viewport3DWorkspace(this))
        , m_wsLyap(new LyapunovWorkspace(this))
    {
        // 1) Заполняем выпадающий список
        m_typeCombo->addItem(tr("3D Viewport"));
        m_typeCombo->addItem(tr("Lyapunov Diagram"));
        // …ещё типы

        // 2) Стек страниц
        m_stack->addWidget(m_ws3d);
        m_stack->addWidget(m_wsLyap);
        // …остальные

        // 3) Вертикальный лэйаут
        auto* lay = new QVBoxLayout(this);
        lay->setContentsMargins(0, 0, 0, 0);
        lay->addWidget(m_typeCombo);
        lay->addWidget(m_stack);
        setLayout(lay);

        // 4) Подключаем сигнал к слоту
        connect(m_typeCombo,
            static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &WorkspaceContainer::onTypeChanged);
    }

    void WorkspaceContainer::onTypeChanged(int index)
    {
        m_stack->setCurrentIndex(index);
    }

} // namespace ODV