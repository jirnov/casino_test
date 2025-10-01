#pragma once

#include "Forward.h"
#include <memory>

class Texture {
public:
    explicit Texture(const Image& image);
    ~Texture();

    void bind(GLenum textureUnit = GL_TEXTURE0) const;

private:
    GLuint m_texture = 0;
    glm::ivec2 m_size;
};