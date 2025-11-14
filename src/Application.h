#pragma once

#include "Forward.h"
#include "GlutCallbacks.h"

class Application : public EventListener {
public:
    Application(int argc, char** argv);
    ~Application();

    int run();

private:
    void onMouseEvent(const MouseEvent& event) override;
    void onKeyboardEvent(const KeyboardEvent& event) override;
    void onReshapeEvent(const ReshapeEvent& event) override;
    void onDisplayEvent(const DisplayEvent& event) override;
    void onTimerEvent(const TimerEvent& event) override;

    SpriteManagerUPtr m_spriteMgr;
    CameraPtr m_camera;
    FPSMetricsUPtr m_metrics;

    Milliseconds m_prevTime{Milliseconds::zero()};

    GameUPtr m_game;

    GlutCallbacksUPtr m_glutCallbacks;
};
