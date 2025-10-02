#include "Mesh.h"

Mesh::Mesh()
{
    glGenVertexArrays(1, &m_vertexArrayObject);
    glGenBuffers(1, &m_vertexBuffer);
    glGenBuffers(1, &m_indexBuffer);

    glBindVertexArray(m_vertexArrayObject);

    // clang-format off
    const GLfloat vertices[] = {
        -1, -1, 0, 0, // left bottom
         1, -1, 1, 0, // right bottom
         1,  1, 1, 1, // right top
        -1,  1, 0, 1  // left top
    };
/*
    const GLfloat vertices[] = {
        0, 64, 0, 0,
        64, 64, 1, 0,
        64, 0, 1, 1,
        0, 0, 0, 1
    };*/
    // clang-format on

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // clang-format off
    const unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    // clang-format on

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // vertex coords (x, y)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // tex coords (u, v)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &m_vertexBuffer);
    glDeleteBuffers(1, &m_indexBuffer);
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::render() const
{
    glBindVertexArray(m_vertexArrayObject);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}