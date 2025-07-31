#pragma once
#include <DockManager.h>
#include <DockWidget.h>
#include <QMainWindow>
#include <QSplitter>
#include <QAction>
#include <QMenuBar>

namespace ODV {

    class MainWindow : public QMainWindow {
        Q_OBJECT
    public:
        explicit MainWindow(QWidget* parent = nullptr);

    private slots:
        void onNewWorkspaceRequested();

    private:
        void addWorkspaceDock(QWidget* workspace, const QString& title);

        ads::CDockManager* m_dockMgr{ nullptr };

        QMenu* m_workspaceMenu{ nullptr };
        QAction* m_actNewWorkspace{ nullptr };
    };

} // namespace ODV