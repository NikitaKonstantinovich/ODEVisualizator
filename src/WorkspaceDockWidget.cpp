#include "WorkspaceDockWidget.h"
#include "Viewport3DWorkspace.h"
#include "LyapunovWorkspace.h"

#include <QComboBox>
#include <QToolButton>
#include <QMenu>
#include <QHBoxLayout>
#include <QAction>
#include <QApplication>

WorkspaceDockWidget::WorkspaceDockWidget(const QString& title, QWidget* parent)
    : QDockWidget(title, parent)
{
    setAllowedAreas(Qt::AllDockWidgetAreas);
    createTitleBar();

    // Сразу создаём 3D-вид
    switchTo(Type::View3D);
    m_typeCombo->setCurrentIndex(int(Type::View3D));
}

void WorkspaceDockWidget::createTitleBar() {
    QWidget* tb = new QWidget(this);
    auto* layout = new QHBoxLayout(tb);
    layout->setContentsMargins(2, 2, 2, 2);

    // Тип workspace
    m_typeCombo = new QComboBox(tb);
    m_typeCombo->addItems({ tr("3D Viewport"), tr("Lyapunov Diagram") });
    layout->addWidget(m_typeCombo);

    // Кнопка Axes
    m_axisButton = new QToolButton(tb);
    m_axisButton->setText(tr("Axes"));
    m_axisButton->setPopupMode(QToolButton::InstantPopup);
    m_axisMenu = new QMenu(m_axisButton);
    QAction* ax = m_axisMenu->addAction(tr("Show X Axis")); ax->setCheckable(true); ax->setChecked(true);
    QAction* ay = m_axisMenu->addAction(tr("Show Y Axis")); ay->setCheckable(true); ay->setChecked(true);
    QAction* az = m_axisMenu->addAction(tr("Show Z Axis")); az->setCheckable(true); az->setChecked(true);
    m_axisButton->setMenu(m_axisMenu);
    layout->addWidget(m_axisButton);

    // Кнопка Grid
    m_gridButton = new QToolButton(tb);
    m_gridButton->setText(tr("Grid"));
    m_gridButton->setPopupMode(QToolButton::InstantPopup);
    m_gridMenu = new QMenu(m_gridButton);
    QAction* gxy = m_gridMenu->addAction(tr("Grid XY")); gxy->setCheckable(true);
    QAction* gyz = m_gridMenu->addAction(tr("Grid YZ")); gyz->setCheckable(true);
    QAction* gzx = m_gridMenu->addAction(tr("Grid ZX")); gzx->setCheckable(true);
    m_gridButton->setMenu(m_gridMenu);
    layout->addWidget(m_gridButton);

    layout->addStretch();
    tb->setLayout(layout);
    setTitleBarWidget(tb);

    connect(m_typeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &WorkspaceDockWidget::onTypeSelected);

    connect(ax, &QAction::toggled, this, &WorkspaceDockWidget::onShowAxisXToggled);
    connect(ay, &QAction::toggled, this, &WorkspaceDockWidget::onShowAxisYToggled);
    connect(az, &QAction::toggled, this, &WorkspaceDockWidget::onShowAxisZToggled);
    connect(gxy, &QAction::toggled, this, &WorkspaceDockWidget::onShowGridXYToggled);
    connect(gyz, &QAction::toggled, this, &WorkspaceDockWidget::onShowGridYZToggled);
    connect(gzx, &QAction::toggled, this, &WorkspaceDockWidget::onShowGridZXToggled);
}

void WorkspaceDockWidget::onTypeSelected(int idx) {
    switchTo(Type(idx));
    emit typeChanged(Type(idx));
}

void WorkspaceDockWidget::switchTo(Type t) {
    if (m_activeWidget) {
        setWidget(nullptr);
        m_activeWidget->deleteLater();
    }
    switch (t) {
    case Type::View3D:
        m_activeWidget = new Viewport3DWorkspace(this);
        break;
    case Type::Lyapunov:
        m_activeWidget = new LyapunovWorkspace(this);
        break;
    default:
        m_activeWidget = new QWidget(this);
    }
    m_type = t;
    setWidget(m_activeWidget);

    // Применяем текущие флаги к 3D‐виджету
    if (auto* vp = qobject_cast<Viewport3DWorkspace*>(m_activeWidget)) {
        vp->setShowAxisX(m_showAxisX);
        vp->setShowAxisY(m_showAxisY);
        vp->setShowAxisZ(m_showAxisZ);
        vp->setShowGridXY(m_showGridXY);
        vp->setShowGridYZ(m_showGridYZ);
        vp->setShowGridZX(m_showGridZX);
    }
}

// Слоты переключения чекбоксов — просто запоминаем состояние и ставим флаг в 3D-виде
void WorkspaceDockWidget::onShowAxisXToggled(bool v) {
    m_showAxisX = v;
    if (auto* vp = qobject_cast<Viewport3DWorkspace*>(m_activeWidget))
         vp->setShowAxisX(v);
}

void WorkspaceDockWidget::onShowAxisYToggled(bool v) {
    m_showAxisY = v;
    if (auto* vp = qobject_cast<Viewport3DWorkspace*>(m_activeWidget))
        vp->setShowAxisY(v);
}

void WorkspaceDockWidget::onShowAxisZToggled(bool v) {
    m_showAxisZ = v;
    if (auto* vp = qobject_cast<Viewport3DWorkspace*>(m_activeWidget))
        vp->setShowAxisZ(v);
}

void WorkspaceDockWidget::onShowGridXYToggled(bool v) {
    m_showGridXY = v;
    if (auto* vp = qobject_cast<Viewport3DWorkspace*>(m_activeWidget))
        vp->setShowGridXY(v);
}

void WorkspaceDockWidget::onShowGridYZToggled(bool v) {
    m_showGridYZ = v;
    if (auto* vp = qobject_cast<Viewport3DWorkspace*>(m_activeWidget))
        vp->setShowGridYZ(v);
}

void WorkspaceDockWidget::onShowGridZXToggled(bool v) {
    m_showGridZX = v;
    if (auto* vp = qobject_cast<Viewport3DWorkspace*>(m_activeWidget))
        vp->setShowGridZX(v);
}