#ifndef WORKSPACEDOCKWIDGET_H
#define WORKSPACEDOCKWIDGET_H

#include <QDockWidget>

class QComboBox;
class QWidget;

class WorkspaceDockWidget : public QDockWidget {
    Q_OBJECT

public:
    enum class Type {
        View3D,
        Lyapunov,
        // Е другие типы по мере роста
    };

    explicit WorkspaceDockWidget(const QString& title, QWidget* parent = nullptr);
    Type currentType() const noexcept { return m_type; }

signals:
    void typeChanged(Type newType);

private slots:
    void onTypeSelected(int index);

private:
    void createTitleBar();
    void switchTo(Type t);

    QComboBox* m_typeCombo;
    QWidget* m_activeWidget = nullptr;
    Type       m_type = Type::View3D;
};

#endif // WORKSPACEDOCKWIDGET_H