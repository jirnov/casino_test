#pragma once

#include "Forward.h"

enum class CellType { Cherry = 0, Lemon, Orange, One, Two, Three, Four, Count };

class Wheel {
    enum class State { Idle, Spin, Deceleration };

public:
    explicit Wheel(const SpriteManager& spriteMgr);

    void setPosition(const glm::vec2& pos);

    void render(const Camera& camera);

    void update(const Milliseconds& dt);

    void startSpin(const Milliseconds& duration);

private:
    void stopSpin();

    std::unordered_map<CellType, SpriteUPtr> m_sprites;

    std::vector<CellType> m_cells;
    float m_currentIndex{0.0f};
    float m_targetIndex{0.0f};

    // Cells per millisecond
    float m_velocity{0.0f};
    float m_acceleration{0.0f};

    Milliseconds m_elapsedTime{0};
    Milliseconds m_targetTime{0};
    Milliseconds m_delerationTime{0};

    State m_state{State::Idle};

    glm::vec2 m_position{0, 0};
};
