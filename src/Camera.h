#pragma once

#include "Forward.h"
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(const glm::ivec2& size);

    void setWindowSize(const glm::ivec2& size);

    const glm::mat4& getProjectionMatrix() const;

private:
    glm::mat4 m_projection = glm::identity<glm::mat4>();
};
