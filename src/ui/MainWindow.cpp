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
                       DockOption::AnimatedDocks);        // плавна€ анимаци€
        setDockNestingEnabled(true);                      // многоуровневое вложение

        // временный центральный пустой виджет, чтобы панель можно было
        // стыковать со всех сторон
        setCentralWidget(new QWidget(this));

        m_workspaceMenu = menuBar()->addMenu(tr("&Workspace"));
        m_actNewWorkspace = m_workspaceMenu->addAction(tr("New workspaceЕ"));
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
        dock->setAttribute(Qt::WA_NativeWindow);          // корректное всплытие на 2-й монитор
        addDockWidget(Qt::LeftDockWidgetArea, dock);      // базова€ позици€

        //  сразу табом к соседней панели:
        // tabifyDockWidget(existingDock, dock);
    }

    void MainWindow::onNewWorkspaceRequested()
    {
        auto* w = new Viewport3DWorkspace(this);          // или другой тип
        addWorkspaceDock(w, tr("Viewport 3D"));
    }

} // namespace ODV
