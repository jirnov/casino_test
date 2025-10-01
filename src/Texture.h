#pragma once

#include "Forward.h"
#include <memory>

class Texture {
public:
    explicit Texture(const Image& image);
    ~Texture();

    void bind(GLenum textureUnit = GL_TEXTURE0) const;
    glm::vec2 dimension() const;

private:
    GLuint m_texture{0};
    glm::uvec2 m_size;
};