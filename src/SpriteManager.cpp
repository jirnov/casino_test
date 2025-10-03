#include "SpriteManager.h"
#include "Image.h"
#include "Mesh.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "Sprite.h"
#include "Texture.h"

SpriteManager::SpriteManager()
   : m_mesh{std::make_shared<Mesh>()}
   , m_shader{ShaderManager::createSpriteShader()}
{}

SpriteUPtr SpriteManager::createSprite(const std::string& name) const
{
    TexturePtr texture;

    auto iter = m_textures.find(name);

    if (iter == m_textures.end()) {
        auto fileName = name + ".png";
        auto image = Image::load(fileName);
        texture = std::make_shared<Texture>(*image);
        m_textures[name] = texture;
    } else {
        texture = iter->second;
    }

    return std::make_unique<Sprite>(texture, m_mesh, m_shader);
}
