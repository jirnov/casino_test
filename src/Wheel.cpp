#include "Wheel.h"
#include "Sprite.h"

Wheel::Wheel(const TextureVector& textures, MeshPtr& mesh, ShaderPtr& shader)
{
    for (int i = 0; i < textures.size(); ++i) {
        auto cellType = static_cast<CellType>(i);
        auto sprite = std::make_unique<Sprite>(textures[i], mesh, shader);

        m_sprites.emplace(std::make_pair(cellType, std::move(sprite)));
    }

    constexpr size_t NUM_CELLS = 70;

    m_cells.resize(NUM_CELLS);

    for (auto& cell : m_cells) {
        cell = static_cast<CellType>(std::rand() % static_cast<int>(CellType::Count));
    }
}

void Wheel::update(const std::chrono::milliseconds& dt)
{
    m_cellIndex += 1.0f * (dt.count() / 1000.0f);

    auto index = static_cast<int>(m_cellIndex);
    auto frac = m_cellIndex - index;

    m_cellIndex = index % m_cells.size() + frac;

    std::cout << index << ", " << frac << "\n";
}

void Wheel::draw(const Camera& camera)
{
    auto firstIndex = static_cast<int>(m_cellIndex);
    auto fracPart = m_cellIndex - firstIndex;

    glm::vec2 startPos{ 0, 256 + fracPart * 64 };

    for (size_t i = 0; i < 4; ++i) {
        auto index = (firstIndex + i) % m_cells.size();

        auto &sprite = m_sprites.at(m_cells[index]);
        sprite->setPosition(startPos - glm::vec2(0, 64 * i));
        sprite->draw(camera);

    }

}
