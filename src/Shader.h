#pragma once

#include "Forward.h"
#include <glm/mat4x4.hpp>
#include <string>

class Shader {
public:
    Shader(const std::string& vertexSource, const std::string& fragmentSource);
    ~Shader();

    void use() const;

    void setUniform1i(const std::string& name, int value) const;
    void setUniform3f(const std::string& name, const glm::vec3& color) const;
    void setUniformMatrix4fv(const std::string& name, const glm::mat4& matrix) const;

private:
    GLuint m_program{0};
};
