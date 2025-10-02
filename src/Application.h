#pragma once

#include "Forward.h"

class Application {
public:
    Application(int argc, char** argv);
    ~Application();

    int run();

private:
    void render();
    void setWindowSize(int w, int h);

    static Application* m_instance;
    Application* m_prevInstance = nullptr;

    ShaderManagerUPtr m_shaderMgr;
    SpriteUPtr m_sprite;
    CameraPtr m_camera;
    FPSMetricsUPtr m_metrics;

    WheelUPtr m_wheel;
};
