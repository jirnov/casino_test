#include "FPSMetrics.h"
#include <format>

void FPSMetrics::update()
{
    ++m_frameCount;

    const auto curTime = glutGet(GLUT_ELAPSED_TIME);
    const auto interval = curTime - m_prevTime;

    if (interval > 1000) {
        const auto frameTime = interval / m_frameCount;
        const auto fps = 1000 / frameTime;
        m_prevTime = curTime;
        m_frameCount = 0;

        m_label = std::format("FPS: {}, frame time = {} ms", fps, frameTime);
    }
}

void FPSMetrics::render()
{
    update();

    if (m_label.empty()) {
        return;
    }
    glColor3f(1, 1, 1);
    glWindowPos2d(0, 0);
    glColor3f(0.0f, 0.0f, 1.0f);
    for (auto c : m_label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}
