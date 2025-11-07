#include "Camera.h"

Camera::Camera(const glm::ivec2& size)
{
    setWindowSize(size);
}

void Camera::setWindowSize(const glm::ivec2& size)
{
    m_projection = glm::ortho(0.0f, static_cast<float>(size.x), static_cast<float>(size.y), 0.0f);
}

const glm::mat4& Camera::getProjectionMatrix() const
{
    return m_projection;
}
