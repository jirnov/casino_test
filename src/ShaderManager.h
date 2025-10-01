#pragma once

#include "Forward.h"

class ShaderManager {
public:
    ShaderManager();

    ShaderPtr getSpriteShader();

private:
    ShaderPtr m_spriteShader;
};