#pragma once

#include "Forward.h"

enum class CellType { Cherry = 0, Lemon, Orange, One, Two, Three, Four, Count };

class Wheel {
public:
    Wheel(const TextureVector& textures, MeshPtr& mesh, ShaderPtr& shader);

    void setPosition(const glm::vec2& pos);

    void draw(const Camera& camera);

    void update(const std::chrono::milliseconds& dt);

private:
    CellType cellByIndex(int index);

    std::unordered_map<CellType, SpriteUPtr> m_sprites;

    std::vector<CellType> m_cells;
    float m_cellIndex;

    //    WheelModelUPtr m_model;
    //WheelViewUPtr m_view;
};