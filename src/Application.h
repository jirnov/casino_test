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
    void onMouse(int button, int state, int x, int y);

    static void timerFunc(int fps);

    static Application* m_instance;
    Application* m_prevInstance = nullptr;

    SpriteManagerUPtr m_spriteMgr;
    CameraPtr m_camera;
    FPSMetricsUPtr m_metrics;

    Milliseconds m_prevTime{Milliseconds::zero()};

    int m_winId{0};

    GameUPtr m_game;
};
