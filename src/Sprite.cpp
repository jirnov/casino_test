#include "Sprite.h"
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

Sprite::Sprite(TexturePtr texture, MeshPtr mesh, ShaderPtr shader)
   : m_texture(std::move(texture))
   , m_mesh(std::move(mesh))
   , m_shader(std::move(shader))
{
    // (-1, 1) -> (0, 1)
    auto ndc2screen = glm::scale(glm::vec3(0.5f)) * glm::translate(glm::vec3(1.0f));
    // (0, 1) -> pixel size
    auto scaleMat = glm::scale(glm::vec3(64, 64, 1));
}

void Sprite::draw(const Camera* camera)
{
    if (!m_shader || !m_texture || !m_mesh) {
        return;
    }

    m_shader->use();
    m_texture->bind(GL_TEXTURE0);

    m_shader->setUniform1i("spriteTexture", 0);
    m_shader->setUniformMatrix4fv("projection", camera->getProjectionMatrix());

    auto projection = camera->getProjectionMatrix();

    // (-1, 1) -> (0, 1)
    auto ndc2screen = glm::scale(glm::vec3(0.5f)) * glm::translate(glm::vec3(1.0f));
    // (0, 1) -> pixel size
    auto scaleMat = glm::scale(glm::vec3(64, 64, 1));
    // move
    auto translateMat = glm::translate(glm::vec3(50, 50, 0));

    auto model = translateMat * scaleMat * ndc2screen;

    m_shader->setUniformMatrix4fv("model", model);

    m_mesh->draw();
}
