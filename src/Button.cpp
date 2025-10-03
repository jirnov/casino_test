#include "Button.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include <glm/gtx/string_cast.hpp>

namespace {
constexpr glm::uvec2 BUTTON_LEFT_TOP{320, 520};
constexpr glm::uvec2 BUTTON_RIGHT_BOTTOM{480, 580};
} // namespace

Button::Button(const SpriteManager& spriteMgr)
{
    m_label = spriteMgr.createSprite("label");
    m_label->setColor(glm::vec3{0, 1, 0});
    m_label->setPosition(glm::vec2{800 / 2 - 128 / 2, 600 - 80});
}

void Button::update(const Milliseconds& dt)
{
    m_labelAnim += m_labelSpeed * (dt.count() / 1000.0f);
    if (m_labelAnim < 0) {
        m_labelAnim = 0;
        m_labelSpeed = -m_labelSpeed;
    } else if (m_labelAnim > 1) {
        m_labelAnim = 1;
        m_labelSpeed = -m_labelSpeed;
    }

    const auto colorA = glm::vec3{1, 0, 0};
    const auto colorB = glm::vec3{0, 1, 0};

    m_label->setColor(colorA + (colorB - colorA) * m_labelAnim);
}

void Button::render(const Camera& camera)
{
    m_label->render(camera);
}

bool Button::clicked(int button, int state, int x, int y) const
{
    if (button != GLUT_LEFT_BUTTON) {
        return false;
    }

    if (state != GLUT_UP) {
        return false;
    }

    const auto lt = BUTTON_LEFT_TOP;
    const auto rb = BUTTON_RIGHT_BOTTOM;

    return (x >= lt.x && x <= rb.x && y >= lt.y && y <= rb.y);
}
