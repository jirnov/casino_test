#pragma once

#include "Forward.h"

class Mesh {
public:
    Mesh();
    ~Mesh();

    void render() const;

private:
    GLuint m_vertexArrayObject{0};
    GLuint m_vertexBuffer{0};
    GLuint m_indexBuffer{0};
};