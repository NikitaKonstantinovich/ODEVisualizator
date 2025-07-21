#pragma once

#include <QMainWindow>
#include <QTabWidget>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void setupMenu();
    void setupStatusBar();
    void onNewWorkspace();
    void onCloseCurrentWorkspace();
    void onWorkspaceChanged(int index);

    QTabWidget* m_workspaceTabs;
    QLabel* m_actionLabel;
    QLabel* m_versionLabel;
};
