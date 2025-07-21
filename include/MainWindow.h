#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTabWidget;
class QLabel;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onNewWorkspace();
    void onCloseCurrentWorkspace();
    void onWorkspaceChanged(int index);

private:
    void setupMenu();
    void setupStatusBar();

    QTabWidget* m_workspaceTabs;
    QLabel* m_actionLabel;
    QLabel* m_versionLabel;
};

#endif // MAINWINDOW_H
