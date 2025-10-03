#include "Game.h"
#include "Button.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Wheel.h"

Game::Game(const SpriteManager& spriteMgr)
   : m_foreground{spriteMgr.createSprite("foreground")}
   , m_button{std::make_unique<Button>(spriteMgr)}
{
    glm::vec2 wheelPos{240 - 2, 332};

    for (int i = 0; i < 5; ++i) {
        auto wheel = std::make_unique<Wheel>(spriteMgr);
        m_wheels.push_back(std::move(wheel));
        m_wheels.back()->setPosition(wheelPos);
        wheelPos.x += 65;
    }
}

Game::~Game()
{}

void Game::startSpin()
{
    const auto minDuration = Milliseconds{Seconds{4}};
    const auto maxDuration = Milliseconds{Seconds{5}};

    auto step = (maxDuration - minDuration) / m_wheels.size();
    auto duration = minDuration;

    for (auto& wheel : m_wheels) {
        wheel->startSpin(duration);
        duration += step;
    }
}

void Game::render(const Camera& camera)
{
    for (auto& wheel : m_wheels) {
        wheel->render(camera);
    }
    m_foreground->render(camera);
    m_button->render(camera);
}

void Game::update(const Milliseconds& dt)
{
    for (auto& wheel : m_wheels) {
        wheel->update(dt);
    }
    m_button->update(dt);
}

void Game::onKeyboard(unsigned char key)
{
    if (key == 32) {
        startSpin();
    }
}

void Game::onMouse(int button, int state, int x, int y)
{
    if (m_button->clicked(button, state, x, y)) {
        startSpin();
    }
}
