#pragma once
#include <QOpenGLFunctions>

namespace ODV {

    class AxisRenderer : protected QOpenGLFunctions {
    public:
        AxisRenderer() = default;

        /// Вызывается один раз из initializeGL()
        void initialize() { initializeOpenGLFunctions(); }

        /// Рисуем красную X, зелёную Y и синюю Z
        void draw();
    };

} // namespace ODV