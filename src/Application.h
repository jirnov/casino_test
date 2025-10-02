#pragma once

#include "Forward.h"

class Application {
public:
    Application(int argc, char** argv);
    ~Application();

    int run();

private:
    void registerCallbacks();
    void unregisterCallbasks();

    void render();
    void setWindowSize(int w, int h);
    void update();
    void onKeyboard(unsigned char key);

    static void timerFunc(int fps);

    static Application* m_instance;
    Application* m_prevInstance = nullptr;

    ShaderManagerUPtr m_shaderMgr;
    SpriteUPtr m_sprite;
    CameraPtr m_camera;
    FPSMetricsUPtr m_metrics;

    SpriteUPtr m_foreground;
    WheelUPtr m_wheel;

    Milliseconds m_prevTime{Milliseconds::zero()};

    int m_winId{0};
};
