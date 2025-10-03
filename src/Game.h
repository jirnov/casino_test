#pragma once

#include "Forward.h"

class Game {
public:
    Game(const SpriteManager& spriteMgr);
    ~Game();

    void update(const Milliseconds& dt);
    void render(const Camera& camera);

    void onMouse(int button, int state, int x, int y);
    void onKeyboard(unsigned char key);

private:
    void startSpin();

    SpriteUPtr m_foreground;
    std::vector<WheelUPtr> m_wheels;
    ButtonUPtr m_button;
};
