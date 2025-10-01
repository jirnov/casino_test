#pragma once

#include "Forward.h"

class FPSMetrics {
public:
    void render();

private:
    void update();

    int m_frameCount{0};
    int m_prevTime{0};
    std::string m_label;
};