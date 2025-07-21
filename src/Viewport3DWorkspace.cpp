#include "Viewport3DWorkspace.h"
#include <GL/gl.h>

Viewport3DWorkspace::Viewport3DWorkspace(QWidget* parent)
    : QOpenGLWidget(parent)
{
}

void Viewport3DWorkspace::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void Viewport3DWorkspace::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void Viewport3DWorkspace::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Простая ортографическая проекция
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = float(width()) / float(height());
    glOrtho(-2 * aspect, 2 * aspect, -2, 2, -10, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Сначала сетка, затем оси
    drawGrid();
    drawAxes();
}

void Viewport3DWorkspace::drawAxes() {
    glBegin(GL_LINES);
    if (m_showAxisX) {
        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0); glVertex3f(1, 0, 0);
    }
    if (m_showAxisY) {
        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0); glVertex3f(0, 1, 0);
    }
    if (m_showAxisZ) {
        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 0); glVertex3f(0, 0, 1);
    }
    glEnd();
}

void Viewport3DWorkspace::drawGrid() {
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);
    float s = m_cameraDistance; // масштаб сетки
    int n = 10;
    if (m_showGridXY) {
        for (int i = -n; i <= n; ++i) {
            float v = i * s;
            // линии вдоль X
            glVertex3f(v, -n * s, 0); glVertex3f(v, n * s, 0);
            // линии вдоль Y
            glVertex3f(-n * s, v, 0); glVertex3f(n * s, v, 0);
        }
    }
    if (m_showGridYZ) {
        for (int i = -n; i <= n; ++i) {
            float v = i * s;
            glVertex3f(0, v, -n * s); glVertex3f(0, v, n * s);
            glVertex3f(0, -n * s, v); glVertex3f(0, n * s, v);
        }
    }
    if (m_showGridZX) {
        for (int i = -n; i <= n; ++i) {
            float v = i * s;
            glVertex3f(-n * s, 0, v); glVertex3f(n * s, 0, v);
            glVertex3f(v, 0, -n * s); glVertex3f(v, 0, n * s);
        }
    }
    glEnd();
}
