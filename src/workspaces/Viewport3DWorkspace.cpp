#include "workspaces/Viewport3DWorkspace.h"
#include <QMouseEvent>
#include <GL/gl.h> 

namespace ODV {

    Viewport3DWorkspace::Viewport3DWorkspace(QWidget* parent)
        : QOpenGLWidget(parent)
    {}

    void Viewport3DWorkspace::initializeGL() {
        initializeOpenGLFunctions();
        glEnable(GL_DEPTH_TEST);
        m_axisRenderer.initialize();
        m_gridRenderer.initialize();
    }

    void Viewport3DWorkspace::resizeGL(int w, int h) {
        glViewport(0, 0, w, h);
        float aspect = float(w) / (h ? h : 1);
        m_camera.setPerspective(45.0f, aspect, 0.1f, 100.0f);
    }

    void Viewport3DWorkspace::paintGL() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(m_camera.projMatrix().constData());
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(m_camera.viewMatrix().constData());

        if (m_showAxisX || m_showAxisY || m_showAxisZ)
            m_axisRenderer.draw();

        float camDist = m_camera.distanceToTarget();
        if (m_showGridXY) m_gridRenderer.draw(ODV::Plane::XY, camDist);
        if (m_showGridYZ) m_gridRenderer.draw(ODV::Plane::YZ, camDist);
        if (m_showGridZX) m_gridRenderer.draw(ODV::Plane::ZX, camDist);
    }

    void Viewport3DWorkspace::mousePressEvent(QMouseEvent* ev) {
        m_lastMousePos = ev->pos();
    }

    void Viewport3DWorkspace::mouseMoveEvent(QMouseEvent* ev) {
        QPoint delta = ev->pos() - m_lastMousePos;
        if (ev->buttons() & Qt::MiddleButton) {
            if (ev->modifiers() & Qt::ShiftModifier)
                m_camera.pan(delta.x() * 0.01f, -delta.y() * 0.01f);
            else if (ev->modifiers() & Qt::ControlModifier)
                m_camera.zoom(-delta.y() * 0.01f);
            else
                m_camera.orbit(delta.x() * 0.5f, delta.y() * 0.5f);
            update();
            m_lastMousePos = ev->pos();
        }
    }

    void Viewport3DWorkspace::wheelEvent(QWheelEvent* ev) {
        float delta = ev->angleDelta().y() / 120.0f * 0.5f;
        m_camera.zoom(-delta);
        update();
    }

} // namespace ODV
