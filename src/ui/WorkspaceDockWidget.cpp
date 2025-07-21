#include "ui/WorkspaceDockWidget.h"
#include "workspaces/Viewport3DWorkspace.h" 

#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>

WorkspaceDockWidget::WorkspaceDockWidget(ODV::Viewport3DWorkspace* vp, QWidget* parent)
    : QDockWidget(tr("Настройки"), parent)
    , m_viewport(vp)
{
    setupUi();
}

void WorkspaceDockWidget::setupUi() {
    QWidget* w = new QWidget(this);
    setWidget(w);
    QVBoxLayout* l = new QVBoxLayout(w);

    l->addWidget(new QLabel(tr("Оси:"), w));
    auto* axX = new QCheckBox(tr("X (красная)"), w); axX->setChecked(true); l->addWidget(axX);
    auto* axY = new QCheckBox(tr("Y (зелёная)"), w); axY->setChecked(true); l->addWidget(axY);
    auto* axZ = new QCheckBox(tr("Z (синяя)"), w);   axZ->setChecked(true); l->addWidget(axZ);

    l->addWidget(new QLabel(tr("Сетки:"), w));
    auto* gXY = new QCheckBox(tr("XY"), w); gXY->setChecked(true); l->addWidget(gXY);
    auto* gYZ = new QCheckBox(tr("YZ"), w);                l->addWidget(gYZ);
    auto* gZX = new QCheckBox(tr("ZX"), w);                l->addWidget(gZX);

    connect(axX, &QCheckBox::toggled, m_viewport, &ODV::Viewport3DWorkspace::setShowAxisX);
    connect(axY, &QCheckBox::toggled, m_viewport, &ODV::Viewport3DWorkspace::setShowAxisY);
    connect(axZ, &QCheckBox::toggled, m_viewport, &ODV::Viewport3DWorkspace::setShowAxisZ);
    connect(gXY, &QCheckBox::toggled, m_viewport, &ODV::Viewport3DWorkspace::setShowGridXY);
    connect(gYZ, &QCheckBox::toggled, m_viewport, &ODV::Viewport3DWorkspace::setShowGridYZ);
    connect(gZX, &QCheckBox::toggled, m_viewport, &ODV::Viewport3DWorkspace::setShowGridZX);
}
