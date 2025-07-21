#ifndef VIEWPORT3DWORKSPACE_H
#define VIEWPORT3DWORKSPACE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class Viewport3DWorkspace : public QOpenGLWidget, protected QOpenGLFunctions {
public:
    explicit Viewport3DWorkspace(QWidget* parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // VIEWPORT3DWORKSPACE_H