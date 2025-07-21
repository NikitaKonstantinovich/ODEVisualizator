#include "MainWindow.h"
#include "WorkspaceDockWidget.h"

#include <QApplication>
#include <QTabWidget>
#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>
#include <QAction>
#include <QWidget>
#include <QObject>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    m_actionLabel(new QLabel(this)),
    m_versionLabel(new QLabel(QString("v%1").arg(QApplication::applicationVersion()), this))
{
    // ����������� ������� ������ ��� ���-�������
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    setupMenu();
    setupStatusBar();

    // ������ ������ ����-������� ������������
    onNewWorkspace();
}

MainWindow::~MainWindow() = default;

void MainWindow::setupMenu() {
    auto fileMenu = menuBar()->addMenu(tr("&File"));
    QAction* newWs = fileMenu->addAction(tr("New Workspace"));
    connect(newWs, &QAction::triggered, this, &MainWindow::onNewWorkspace);

    QAction* closeWs = fileMenu->addAction(tr("Close Workspace"));
    connect(closeWs, &QAction::triggered, this, &MainWindow::onCloseAllWorkspaces);

    fileMenu->addSeparator();
    QAction* exitApp = fileMenu->addAction(tr("Exit"));
    connect(exitApp, &QAction::triggered, qApp, &QApplication::quit);

    menuBar()->addMenu(tr("&View"));  // ���� �������� ��� ������� �������
}

void MainWindow::setupStatusBar() {
    // ����� � ��������, ������ � ������
    statusBar()->addWidget(m_actionLabel, 1);
    statusBar()->addPermanentWidget(m_versionLabel);
}

void MainWindow::onNewWorkspace() {
    static int counter = 1;
    // ������ ���-������ Blender-style
    auto* dock = new WorkspaceDockWidget(tr("Workspace %1").arg(counter++), this);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->show();

    m_actionLabel->setText(tr("Created workspace %1").arg(counter - 1));
}

void MainWindow::onCloseAllWorkspaces() {
    // ��������� ��� WorkspaceDockWidget
    const auto docks = this->findChildren<WorkspaceDockWidget*>();
    for (WorkspaceDockWidget* dock : docks) {
        dock->close();
    }
    m_actionLabel->setText(tr("Closed all workspaces"));
}

