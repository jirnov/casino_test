#include "Texture.h"
#include "Image.h"

Texture::Texture(const Image& image)
   : m_size{image.width(), image.height()}
{
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    constexpr GLenum formats[] = {GL_RED, GL_RG, GL_RGB, GL_RGBA};
    GLenum format = formats[image.numChannels() - 1];

    glTexImage2D(GL_TEXTURE_2D, 0, format, m_size.x, m_size.y, 0, format, GL_UNSIGNED_BYTE, image.pixels());

    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_texture);
}

void Texture::bind(GLenum textureUnit) const
{
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

glm::vec2 Texture::dimension() const
{
    return m_size;
}
