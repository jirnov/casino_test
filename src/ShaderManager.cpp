#include "ShaderManager.h"
#include "Shader.h"

ShaderManager::ShaderManager()
{
    std::string vertexSource = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;
        layout (location = 1) in vec2 aTexCoord;
            
        out vec2 TexCoord;
            
        uniform mat4 model;
        uniform mat4 projection;
            
        void main() {
            gl_Position = vec4(aPos, 0.0, 1.0);
            gl_Position = projection * model * vec4(aPos, 0.0, 1.0);
            TexCoord = aTexCoord;
        }
    )";

    std::string fragmentSource = R"(
        #version 330 core
        in vec2 TexCoord;
        out vec4 FragColor;
            
        uniform sampler2D spriteTexture;
            
        void main() {
            FragColor = texture(spriteTexture, TexCoord);
        }
    )";

    m_spriteShader = std::make_unique<Shader>(vertexSource, fragmentSource);
}

ShaderPtr ShaderManager::getSpriteShader()
{
    return m_spriteShader;
}
