#ifndef VIEWPORT3DWORKSPACE_H
#define VIEWPORT3DWORKSPACE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QObject>  // для Q_OBJECT

class Viewport3DWorkspace : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
public:
    explicit Viewport3DWorkspace(QWidget* parent = nullptr);

public slots:
    void setShowAxisX(bool show) { m_showAxisX = show; update(); }
    void setShowAxisY(bool show) { m_showAxisY = show; update(); }
    void setShowAxisZ(bool show) { m_showAxisZ = show; update(); }
    void setShowGridXY(bool show) { m_showGridXY = show; update(); }
    void setShowGridYZ(bool show) { m_showGridYZ = show; update(); }
    void setShowGridZX(bool show) { m_showGridZX = show; update(); }

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    // Флаги видимости
    bool m_showAxisX = true;
    bool m_showAxisY = true;
    bool m_showAxisZ = true;
    bool m_showGridXY = false;
    bool m_showGridYZ = false;
    bool m_showGridZX = false;

    // Масштаб сетки (будет привязан к камере)
    float m_cameraDistance = 1.0f;

    // Вспомогательные методы
    void drawAxes();
    void drawGrid();
};

#endif // VIEWPORT3DWORKSPACE_H
