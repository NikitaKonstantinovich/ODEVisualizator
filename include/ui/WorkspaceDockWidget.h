#pragma once

#include <QDockWidget>
#include <QComboBox>
#include <QStackedWidget>
#include <QHBoxLayout>

namespace ODV {
    class Viewport3DWorkspace;
}

class WorkspaceDockWidget : public QDockWidget {
    Q_OBJECT
public:
    explicit WorkspaceDockWidget(ODV::Viewport3DWorkspace* viewport, QWidget* parent = nullptr);

private:
    void setupUi();

    ODV::Viewport3DWorkspace* m_viewport;
};