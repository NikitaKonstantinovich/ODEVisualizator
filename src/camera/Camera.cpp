#include "camera/Camera.h"
#include <QtMath>

namespace ODV {

    Camera::Camera()
        : m_eye(0, 0, 5), m_target(0, 0, 0), m_up(0, 1, 0), m_yaw(0), m_pitch(0)
    {
        updateViewMatrix();
    }

    void Camera::setPerspective(float fov, float aspect, float zNear, float zFar) {
        m_proj.setToIdentity();
        m_proj.perspective(fov, aspect, zNear, zFar);
    }

    void Camera::orbit(float dx, float dy) {
        m_yaw += dx;
        m_pitch += dy;
        float r = distanceToTarget();
        float y = qDegreesToRadians(m_pitch);
        float a = qDegreesToRadians(m_yaw);
        m_eye.setX(m_target.x() + r * qCos(y) * qSin(a));
        m_eye.setY(m_target.y() + r * qSin(y));
        m_eye.setZ(m_target.z() + r * qCos(y) * qCos(a));
        updateViewMatrix();
    }

    void Camera::pan(float dx, float dy) {
        QVector3D forward = (m_target - m_eye).normalized();
        QVector3D right = QVector3D::crossProduct(forward, m_up).normalized();
        QVector3D up = QVector3D::crossProduct(right, forward).normalized();
        QVector3D delta = -right * dx + up * dy;
        m_eye += delta;
        m_target += delta;
        updateViewMatrix();
    }

    void Camera::zoom(float delta) {
        QVector3D dir = (m_target - m_eye).normalized();
        m_eye += dir * delta;
        updateViewMatrix();
    }

    void Camera::updateViewMatrix() {
        m_view.setToIdentity();
        m_view.lookAt(m_eye, m_target, m_up);
    }

} // namespace ODV
