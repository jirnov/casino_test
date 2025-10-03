#include "FPSMetrics.h"
#include <format>

void FPSMetrics::update(const Milliseconds& dt)
{
    ++m_frameCount;

    m_totalFrameTime += dt;

    if (m_totalFrameTime > Seconds{1}) {
        updateLabel(m_totalFrameTime / m_frameCount);
        m_totalFrameTime = Milliseconds::zero();
        m_frameCount = 0;
    }
}

void FPSMetrics::render()
{
    glColor3f(1, 1, 1);
    glRasterPos2f(0, 0);
    glWindowPos2d(0, 0);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char*>(m_label.c_str()));
    // Есть подозрение, что правильно работать с текстом лучше через FreeType, на всякий случай вывожу в консоль
    //    std::cout << m_label << '\n';
}

void FPSMetrics::updateLabel(const Milliseconds& frameTime)
{
    if (frameTime.count() > 0) {
        m_label = std::format("FPS: {}, frame time = {} ms", 1000 / frameTime.count(), frameTime.count());
    }
}
