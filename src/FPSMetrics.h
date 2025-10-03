#pragma once

#include "Forward.h"

class FPSMetrics {
public:
    void update(const Milliseconds& dt);
    void render();

private:
    void updateLabel(const Milliseconds& frameTime);

    size_t m_frameCount{0};
    Milliseconds m_totalFrameTime{Milliseconds::zero()};
    std::string m_label{"Collecting..."};
};
