#pragma once

#include "Forward.h"

class Button {
public:
    Button(const SpriteManager& spriteMgr);

    void update(const Milliseconds& dt);
    void render(const Camera& camera);

    bool clicked(int button, int state, int x, int y) const;

private:
    SpriteUPtr m_label;
    float m_labelAnim{0.0f};
    float m_labelSpeed{1.0f};
};
