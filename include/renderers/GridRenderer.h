#pragma once
#include <QOpenGLFunctions>

namespace ODV {

    enum class Plane { XY, YZ, ZX };

    class GridRenderer : protected QOpenGLFunctions {
    public:
        GridRenderer() = default;

        /// Вызывается один раз из initializeGL()
        void initialize() { initializeOpenGLFunctions(); }

        /// Рисуем сетку в заданной плоскости, с масштабом от cameraDistance
        void draw(Plane plane, float cameraDistance);
    };

} // namespace ODV
