#include "renderers/AxisRenderer.h"
#include <GL/gl.h>

namespace ODV {

    void AxisRenderer::draw() {
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        // X Ч красна€
        glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0);
        // Y Ч зелЄна€
        glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0);
        // Z Ч син€€
        glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1);
        glEnd();
    }

} // namespace ODV
