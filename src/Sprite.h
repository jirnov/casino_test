#pragma once

#include "Forward.h"
#include <memory>

class Sprite {
public:
    Sprite(TexturePtr texture, MeshPtr mesh, ShaderPtr shader);

    void draw(const Camera& camera);

    void setPosition(const glm::vec2& pos);

private:
    TexturePtr m_texture;
    MeshPtr m_mesh;
    ShaderPtr m_shader;

    // (-1, 1) -> (0, textureSize)
    glm::mat4 m_ndc2pix{glm::identity<glm::mat4>()};
    glm::mat4 m_transform{glm::identity<glm::mat4>()};
};
