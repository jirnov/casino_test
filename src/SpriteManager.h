#pragma once

#include "Forward.h"

class SpriteManager {
public:
    SpriteManager();

    SpriteUPtr createSprite(const std::string& name) const;

private:
    mutable std::unordered_map<std::string, TexturePtr> m_textures;
    MeshPtr m_mesh;
    ShaderPtr m_shader;
};
