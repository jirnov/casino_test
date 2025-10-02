#include <cstdint>
#include <iostream>
#include <memory>

// clang-format off
#include <GL/glew.h>
#include <GL/freeglut.h>
// clang-format on

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <chrono>

// Forward declaration
class Application;
class Camera;
class FPSMetrics;
class Image;
class Mesh;
class Renderer;
class Shader;
class Sprite;
class Texture;
class ShaderManager;
class Wheel;

using MeshPtr = std::shared_ptr<Mesh>;
using TexturePtr = std::shared_ptr<Texture>;
using TextureVector = std::vector<TexturePtr>;

using ShaderPtr = std::shared_ptr<Shader>;

//using RendererUPtr = std::unique_ptr<Renderer>;

using ShaderManagerUPtr = std::unique_ptr<ShaderManager>;

using SpriteUPtr = std::unique_ptr<Sprite>;
using SpriteVector = std::vector<SpriteUPtr>;

using ImageUPtr = std::unique_ptr<Image>;

using CameraPtr = std::shared_ptr<Camera>;

using FPSMetricsUPtr = std::unique_ptr<FPSMetrics>;

using WheelUPtr = std::unique_ptr<Wheel>;

using Milliseconds = std::chrono::milliseconds;