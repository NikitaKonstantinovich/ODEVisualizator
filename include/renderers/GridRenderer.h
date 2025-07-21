#pragma once
#include <QOpenGLFunctions>

namespace ODV {

    enum class Plane { XY, YZ, ZX };

    class GridRenderer : protected QOpenGLFunctions {
    public:
        GridRenderer() = default;

        /// ���������� ���� ��� �� initializeGL()
        void initialize() { initializeOpenGLFunctions(); }

        /// ������ ����� � �������� ���������, � ��������� �� cameraDistance
        void draw(Plane plane, float cameraDistance);
    };

} // namespace ODV
