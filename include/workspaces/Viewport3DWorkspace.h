#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QWheelEvent>
#include "camera/Camera.h"
#include "renderers/AxisRenderer.h"
#include "renderers/GridRenderer.h"

namespace ODV {

    class Viewport3DWorkspace : public QOpenGLWidget, protected QOpenGLFunctions {
        Q_OBJECT
    public:
        explicit Viewport3DWorkspace(QWidget* parent = nullptr);

        void setShowAxisX(bool) { m_showAxisX = true; update(); }
        void setShowAxisY(bool) { m_showAxisY = true; update(); }
        void setShowAxisZ(bool) { m_showAxisZ = true; update(); }
        void setShowGridXY(bool b) { m_showGridXY = b; update(); }
        void setShowGridYZ(bool b) { m_showGridYZ = b; update(); }
        void setShowGridZX(bool b) { m_showGridZX = b; update(); }

    protected:
        void initializeGL() override;
        void resizeGL(int w, int h) override;
        void paintGL() override;

        void mousePressEvent(QMouseEvent* ev) override;
        void mouseMoveEvent(QMouseEvent* ev) override;
        void wheelEvent(QWheelEvent* ev) override;

    private:
        ODV::Camera      m_camera;
        ODV::AxisRenderer m_axisRenderer;
        ODV::GridRenderer m_gridRenderer;

        bool m_showAxisX = true;
        bool m_showAxisY = true;
        bool m_showAxisZ = true;
        bool m_showGridXY = true;
        bool m_showGridYZ = false;
        bool m_showGridZX = false;

        QPoint m_lastMousePos;
    };

} // namespace 
