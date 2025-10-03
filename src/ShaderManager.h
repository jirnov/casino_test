#pragma once

#include "Forward.h"

class ShaderManager {
public:
    static ShaderPtr createSpriteShader();

private:
    ShaderPtr m_spriteShader;
};
