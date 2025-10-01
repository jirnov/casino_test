#pragma once

#include "Forward.h"
#include <memory>

class Sprite {
public:
    Sprite(TexturePtr texture, MeshPtr mesh, ShaderPtr shader);

    void draw(const Camera* camera);

private:
    TexturePtr m_texture;
    MeshPtr m_mesh;
    ShaderPtr m_shader;

    glm::mat4 m_ndc2pix;
    glm::mat4 m_translate;
};
