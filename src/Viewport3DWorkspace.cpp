#include "Viewport3DWorkspace.h"
#include <QSurfaceFormat>

Viewport3DWorkspace::Viewport3DWorkspace(QWidget* parent)
    : QOpenGLWidget(parent)
{
    QSurfaceFormat fmt = QSurfaceFormat::defaultFormat();
    setFormat(fmt);
}

void Viewport3DWorkspace::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void Viewport3DWorkspace::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void Viewport3DWorkspace::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // TODO: отрисовка осей, точек, траекторий
}
