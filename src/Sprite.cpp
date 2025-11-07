#include "Sprite.h"
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

Sprite::Sprite(TexturePtr texture, MeshPtr mesh, ShaderPtr shader)
   : m_texture(texture)
   , m_mesh(mesh)
   , m_shader(shader)
{
    // (-1, 1) -> (0, 1)
    auto ndc2screen = glm::scale(glm::vec3(0.5f)) * glm::translate(glm::vec3(1.0f));
    // (0, 1) -> (0, textureSize)
    m_ndc2pix = glm::scale(glm::vec3(m_texture->dimension(), 1)) * ndc2screen;

    setPosition({});
}

Sprite::~Sprite()
{}

void Sprite::render(const Camera& camera)
{
    if (!m_shader || !m_texture || !m_mesh) {
        return;
    }

    m_shader->use();
    m_texture->bind(GL_TEXTURE0);

    m_shader->setUniform1i("spriteTexture", 0);
    m_shader->setUniform3f("spriteColor", m_color);
    m_shader->setUniformMatrix4fv("projection", camera.getProjectionMatrix());
    m_shader->setUniformMatrix4fv("model", m_transform);

    m_mesh->render();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Sprite::setPosition(const glm::vec2& pos)
{
    m_transform = glm::translate(glm::vec3(pos, 0)) * m_ndc2pix;
}

void Sprite::setColor(const glm::vec3& rgb)
{
    m_color = rgb;
}
