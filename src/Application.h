#pragma once

#include "Forward.h"
#include "GlutCallbacks.h"

class Application : ITimerListener, IDisplayListener, IReshapeListener, IKeyboardListener {
public:
    Application(int argc, char** argv);
    ~Application();

    int run();

private:
    void onTimer(const Milliseconds& dt) override;
    void onRender() override;
    void onReshape(const glm::uvec2& windowSize) override;
    void onKeyboard(KeyCode keyCode) override;

    GlutCallbacksUPtr m_glutCallbacks;

    SpriteManagerUPtr m_spriteMgr;
    CameraPtr m_camera;
    FPSMetricsUPtr m_metrics;

    Milliseconds m_prevTime{Milliseconds::zero()};

    GameUPtr m_game;
};
