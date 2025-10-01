#include "Shader.h"
#include <format>
#include <glm/gtc/type_ptr.hpp>

namespace {
void checkCompileErrors(GLuint shader, const std::string& type)
{
    GLint success;
    GLchar infoLog[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            throw std::runtime_error(std::format("SHADER_COMPILATION_ERROR: {}\nOutput:\n{}\n", type, infoLog));
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            throw std::runtime_error(std::format("PROGRAM_LINKING_ERROR: {}\nOutput:\n{}\n", type, infoLog));
        }
    }
}

GLuint compileShader(GLenum type, const std::string& source)
{
    GLuint shader = glCreateShader(type);
    const char* sourceCStr = source.c_str();
    glShaderSource(shader, 1, &sourceCStr, nullptr);
    glCompileShader(shader);
    checkCompileErrors(shader, type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
    return shader;
}

} // namespace

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
   : m_program(glCreateProgram())
{
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);
    glLinkProgram(m_program);

    checkCompileErrors(m_program, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_program);
}

void Shader::use() const
{
    glUseProgram(m_program);
}

void Shader::setUniform1i(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
}

void Shader::setUniformMatrix4fv(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}
