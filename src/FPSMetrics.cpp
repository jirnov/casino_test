#include "FPSMetrics.h"
#include <format>

void FPSMetrics::update(const Milliseconds& dt)
{
    ++m_frameCount;

    m_totalFrameTime += dt;

    if (m_totalFrameTime.count() > 1000) {
        updateLabel(m_totalFrameTime / m_frameCount);
        m_totalFrameTime = Milliseconds::zero();
        m_frameCount = 0;
    }
}

void FPSMetrics::render()
{
    if (m_label.empty()) {
        return;
    }
    glColor3f(0, 0, 0);
    glRasterPos2d(0, 0);
    glWindowPos2d(0, 0);
    for (auto c : m_label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void FPSMetrics::updateLabel(const Milliseconds& frameTime)
{
    if (frameTime.count() > 0) {
        m_label = std::format("FPS: {}, frame time = {} ms", 1000 / frameTime.count(), frameTime.count());
    }
}
