#pragma once

#include "Forward.h"
#include "GlutCallbacks.h"

class Game : public IMouseListener, public IKeyboardListener {
public:
    Game(const SpriteManager& spriteMgr);
    ~Game();

    void update(const Milliseconds& dt);
    void render(const Camera& camera);

    void onKeyboard(KeyCode code) override;

private:
    void onMouse(MouseButton button, MouseState state, const glm::ivec2 &pos) override;

    void startSpin();

    SpriteUPtr m_foreground;
    std::vector<WheelUPtr> m_wheels;
    ButtonUPtr m_button;
};
