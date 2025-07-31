#include "ui/MainWindow.h"
#include "ui/WorkspaceContainer.h"

#include <QSplitter>
#include <QMenuBar>
#include <QAction>

namespace ODV {

    MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent)
    {
        setDockOptions(DockOption::AllowTabbedDocks |
                       DockOption::AllowNestedDocks |
                       DockOption::AnimatedDocks);        // ������� ��������
        setDockNestingEnabled(true);                      // �������������� ��������

        // ��������� ����������� ������ ������, ����� ������ ����� ����
        // ��������� �� ���� ������
        setCentralWidget(new QWidget(this));

        m_workspaceMenu = menuBar()->addMenu(tr("&Workspace"));
        m_actNewWorkspace = m_workspaceMenu->addAction(tr("New workspace�"));
        connect(m_actNewWorkspace, &QAction::triggered,
            this, &MainWindow::onNewWorkspaceRequested);
    }

    void MainWindow::addWorkspaceDock(QWidget* workspace,
        const QString& title)
    {
        auto* dock = new QDockWidget(title, this);
        dock->setWidget(workspace);
        dock->setAllowedAreas(Qt::AllDockWidgetAreas);
        dock->setFeatures(QDockWidget::DockWidgetMovable |
            QDockWidget::DockWidgetFloatable |
            QDockWidget::DockWidgetClosable);
        dock->setAttribute(Qt::WA_NativeWindow);          // ���������� �������� �� 2-� �������
        addDockWidget(Qt::LeftDockWidgetArea, dock);      // ������� �������

        //  ����� ����� � �������� ������:
        // tabifyDockWidget(existingDock, dock);
    }

    void MainWindow::onNewWorkspaceRequested()
    {
        auto* w = new Viewport3DWorkspace(this);          // ��� ������ ���
        addWorkspaceDock(w, tr("Viewport 3D"));
    }

} // namespace ODV
