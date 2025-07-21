#ifndef WORKSPACEDOCKWIDGET_H
#define WORKSPACEDOCKWIDGET_H

#include <QDockWidget>

class QComboBox;
class QWidget;
class QToolButton;
class QMenu;

class WorkspaceDockWidget : public QDockWidget {
    Q_OBJECT

public:
    enum class Type {
        View3D,
        Lyapunov,
        // Е другие типы по мере роста
    };

    explicit WorkspaceDockWidget(const QString& title, QWidget* parent = nullptr);
    //Type currentType() const noexcept { return m_type; }

signals:
    void typeChanged(Type newType);

private slots:
    void onTypeSelected(int index);
    void onShowAxisXToggled(bool);
    void onShowAxisYToggled(bool);
    void onShowAxisZToggled(bool);
    void onShowGridXYToggled(bool);
    void onShowGridYZToggled(bool);
    void onShowGridZXToggled(bool);

private:
    void createTitleBar();
    void switchTo(Type t);

    QComboBox* m_typeCombo = nullptr;
    QToolButton* m_axisButton = nullptr;
    QMenu* m_axisMenu = nullptr;
    QToolButton* m_gridButton = nullptr;
    QMenu* m_gridMenu = nullptr;
    QWidget* m_activeWidget = nullptr;
    Type          m_type = Type::View3D;

    // сохран€ем состо€ние чекбоксов
    bool m_showAxisX = true;
    bool m_showAxisY = true;
    bool m_showAxisZ = true;
    bool m_showGridXY = false;
    bool m_showGridYZ = false;
    bool m_showGridZX = false;
};

#endif // WORKSPACEDOCKWIDGET_H