#include "ui/MainWindow.h"
#include "ui/WorkspaceContainer.h"

//#include <QSplitter>
#include <QMenuBar>
#include <QAction>

#include <DockManager.h>
#include <DockWidget.h>

namespace ODV {

    MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent)
    {
        //setDockOptions(DockOption::AllowTabbedDocks |
        //               DockOption::AllowNestedDocks |
        //               DockOption::AnimatedDocks);        // ������� ��������
        //setDockNestingEnabled(true);                      // �������������� ��������

        //// ��������� ����������� ������ ������, ����� ������ ����� ����
        //// ��������� �� ���� ������
        //setCentralWidget(new QWidget(this));
        using ads::CDockManager;
        CDockManager::setConfigFlags(CDockManager::DefaultOpaqueConfig);   // ���������� ����� :contentReference[oaicite:4]{index=4}

        m_dockMgr = new CDockManager(this);           // ������ ��������

        m_workspaceMenu = menuBar()->addMenu(tr("&Workspace"));
        m_actNewWorkspace = m_workspaceMenu->addAction(tr("New workspace�"));
        connect(m_actNewWorkspace, &QAction::triggered,
            this, &MainWindow::onNewWorkspaceRequested);
    }

    void MainWindow::addWorkspaceDock(QWidget* workspace,
        const QString& title)
    {
        auto* dock = new ads::CDockWidget(title, this);
        dock->setWidget(workspace);
        m_dockMgr->addDockWidget(ads::CenterDockWidgetArea, dock);

        //  ����� ����� � �������� ������:
        // tabifyDockWidget(existingDock, dock);
    }

    void MainWindow::onNewWorkspaceRequested()
    {
        auto* w = new Viewport3DWorkspace(this);          // ��� ������ ���
        addWorkspaceDock(w, tr("Viewport 3D"));
    }

} // namespace ODV
