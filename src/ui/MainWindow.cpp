#include "ui/MainWindow.h"
#include "workspaces/Viewport3DWorkspace.h"   
#include <QApplication>
#include <QTabWidget>
#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>
#include <QAction>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    m_workspaceTabs(new QTabWidget(this)),
    m_actionLabel(new QLabel(this)),
    m_versionLabel(new QLabel(QString("v%1").arg(QApplication::applicationVersion()), this))
{
    setCentralWidget(m_workspaceTabs);

    setupMenu();
    setupStatusBar();

    // —оздаем первое пустое пространство
    onNewWorkspace();
    connect(m_workspaceTabs, &QTabWidget::currentChanged,
        this, &MainWindow::onWorkspaceChanged);
}

MainWindow::~MainWindow() = default;

void MainWindow::setupMenu() {
    auto fileMenu = menuBar()->addMenu(tr("&File"));
    QAction* newWs = fileMenu->addAction(tr("New Workspace"));
    connect(newWs, &QAction::triggered, this, &MainWindow::onNewWorkspace);

    QAction* closeWs = fileMenu->addAction(tr("Close Workspace"));
    connect(closeWs, &QAction::triggered, this, &MainWindow::onCloseCurrentWorkspace);

    fileMenu->addSeparator();
    QAction* exitApp = fileMenu->addAction(tr("Exit"));
    connect(exitApp, &QAction::triggered, qApp, &QApplication::quit);

    menuBar()->addMenu(tr("&View"));  // пока заглушка дл€ будущих пунктов
}

void MainWindow::setupStatusBar() {
    statusBar()->addWidget(m_actionLabel, 1);
    statusBar()->addPermanentWidget(m_versionLabel);
}

void MainWindow::onNewWorkspace() {
    int count = m_workspaceTabs->count() + 1;
    // теперь класс в неймспейсе ODV::workspace
    auto* page = new ODV::Viewport3DWorkspace(this);
    m_workspaceTabs->addTab(page, tr("Workspace %1").arg(count));
    m_workspaceTabs->setCurrentWidget(page);
    m_actionLabel->setText(tr("Created workspace %1").arg(count));
}

void MainWindow::onCloseCurrentWorkspace() {
    int idx = m_workspaceTabs->currentIndex();
    if (idx >= 0) {
        m_workspaceTabs->removeTab(idx);
        m_actionLabel->setText(tr("Closed workspace %1").arg(idx + 1));
    }
}

void MainWindow::onWorkspaceChanged(int index) {
    if (index >= 0)
        m_actionLabel->setText(tr("Switched to workspace %1").arg(index + 1));
    else
        m_actionLabel->clear();
}
