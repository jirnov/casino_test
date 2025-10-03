#include "Wheel.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include <algorithm>
#include <cmath>

namespace {
constexpr auto NUM_CELLS = 70;
constexpr auto NUM_TYPES = static_cast<size_t>(CellType::Count);
constexpr auto CELLS_PER_MILLIS = 15.0f / 1000.0f;
constexpr auto DECELERATION_TIME = Milliseconds{100};
constexpr auto MIN_VELOCITY = 0.3f / 1000.0f;

float randFloat(float min, float max)
{
    auto p = rand() / static_cast<float>(RAND_MAX);
    return min + (max - min) * p;
}
} // namespace

Wheel::Wheel(const SpriteManager& spriteMgr)
{
    for (size_t i = 0; i < static_cast<size_t>(CellType::Count); ++i) {

        auto name = std::format("image{}", i + 1);
        auto cellType = static_cast<CellType>(i);
        m_sprites[cellType] = spriteMgr.createSprite(name);
    }

    m_cells.resize(NUM_CELLS);

    for (auto& cell : m_cells) {
        cell = static_cast<CellType>(std::rand() % NUM_TYPES);
    }
}

void Wheel::startSpin(const Milliseconds& duration)
{
    if (m_state != State::Idle) {
        return;
    }

    m_elapsedTime = Milliseconds::zero();
    m_targetTime = duration;

    // Текущий индекс приводим в пределы 0..numCells
    m_currentIndex = std::fmod(m_currentIndex, static_cast<float>(m_cells.size()));

    // Вычисляем будущий индекс от заданного времени как целое число
    m_targetIndex = ceilf(m_currentIndex + CELLS_PER_MILLIS * duration.count());

    auto totalCells = m_targetIndex - m_currentIndex;

    m_velocity = totalCells / duration.count();

    auto t = DECELERATION_TIME.count() * randFloat(0.85f, 1.15f);

    m_delerationTime = Milliseconds{static_cast<int>(t)};

    m_elapsedTime = Milliseconds::zero();

    m_state = State::Spin;
}

void Wheel::stopSpin()
{
    m_state = State::Idle;
    m_currentIndex = m_targetIndex;
    m_velocity = 0;
}

void Wheel::update(const Milliseconds& dt)
{
    switch (m_state) {
        case State::Idle:
            return;

        case State::Spin: {
            m_elapsedTime += dt;
            m_currentIndex += m_velocity * dt.count();

            const auto timeRemaining = m_targetTime - m_elapsedTime;

            if (timeRemaining <= m_delerationTime) {
                m_acceleration = -m_velocity / timeRemaining.count();
                m_state = State::Deceleration;
            }

            if (m_currentIndex >= m_targetIndex) {
                stopSpin();
            }
        } break;

        case State::Deceleration: {
            auto newVelocity = m_velocity + m_acceleration * dt.count();
            if (newVelocity > MIN_VELOCITY) {
                m_velocity = newVelocity;
            }
            m_currentIndex += m_velocity * dt.count();

            if (m_currentIndex >= m_targetIndex) {
                stopSpin();
            }

            break;
        }
    }
}

void Wheel::render(const Camera& camera)
{
    auto firstIndex = static_cast<int>(m_currentIndex);
    auto fracPart = m_currentIndex - firstIndex;
    firstIndex = firstIndex % m_cells.size();

    const auto startPos = m_position + glm::vec2{0, fracPart * 64};

    for (size_t i = 0; i < 4; ++i) {
        auto index = (firstIndex + i) % m_cells.size();

        auto& sprite = m_sprites.at(m_cells[index]);
        sprite->setPosition(startPos - glm::vec2(0, 65 * i));
        sprite->render(camera);
    }
}

void Wheel::setPosition(const glm::vec2& pos)
{
    m_position = pos;
}
