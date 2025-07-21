#pragma once
#include <QOpenGLFunctions>

namespace ODV {

    class AxisRenderer : protected QOpenGLFunctions {
    public:
        AxisRenderer() = default;

        /// ���������� ���� ��� �� initializeGL()
        void initialize() { initializeOpenGLFunctions(); }

        /// ������ ������� X, ������ Y � ����� Z
        void draw();
    };

} // namespace ODV