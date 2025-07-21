#include "renderers/GridRenderer.h"
#include <GL/gl.h>
#include <cmath>

namespace ODV {

    void GridRenderer::draw(Plane plane, float cameraDistance) {
        const float spacing = std::max(1.0f, cameraDistance * 0.1f);
        const int count = 20;
        glLineWidth(1.0f);
        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_LINES);
        for (int i = -count; i <= count; ++i) {
            float d = i * spacing;
            switch (plane) {
            case Plane::XY:
                glVertex3f(d, -count * spacing, 0); glVertex3f(d, count * spacing, 0);
                glVertex3f(-count * spacing, d, 0); glVertex3f(count * spacing, d, 0);
                break;
            case Plane::YZ:
                glVertex3f(0, d, -count * spacing); glVertex3f(0, d, count * spacing);
                glVertex3f(0, -count * spacing, d); glVertex3f(0, count * spacing, d);
                break;
            case Plane::ZX:
                glVertex3f(-count * spacing, 0, d); glVertex3f(count * spacing, 0, d);
                glVertex3f(d, 0, -count * spacing); glVertex3f(d, 0, count * spacing);
                break;
            }
        }
        glEnd();
    }

} // namespace ODV