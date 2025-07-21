#pragma once
#include <QVector3D>
#include <QMatrix4x4>

namespace ODV {

    class Camera {
    public:
        Camera();

        void setPerspective(float fov, float aspect, float zNear, float zFar);
        void orbit(float dx, float dy);
        void pan(float dx, float dy);
        void zoom(float delta);

        const QMatrix4x4& viewMatrix() const { return m_view; }
        const QMatrix4x4& projMatrix() const { return m_proj; }
        float distanceToTarget() const { return (m_eye - m_target).length(); }

    private:
        void updateViewMatrix();

        QMatrix4x4 m_view;
        QMatrix4x4 m_proj;
        QVector3D   m_eye;
        QVector3D   m_target;
        QVector3D   m_up;
        float       m_yaw, m_pitch;
    };

} // namespace ODV
