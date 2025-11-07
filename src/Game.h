#pragma once

#include "Forward.h"
#include "GlutCallbacks.h"

class Game : EventListener {
public:
    Game(const SpriteManager& spriteMgr);
    ~Game();

    void update(const Milliseconds& dt);
    void render(const Camera& camera);

    void onKeyboardEvent(const KeyboardEvent& event) override;
    void onMouseEvent(const MouseEvent& event) override;

private:
    void startSpin();

    SpriteUPtr m_foreground;
    std::vector<WheelUPtr> m_wheels;
    ButtonUPtr m_button;
};
