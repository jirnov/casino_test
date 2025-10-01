#include "Application.h"
#include "Camera.h"
#include "Image.h"
#include "Mesh.h"
#include "ShaderManager.h"
#include "Sprite.h"
#include "Texture.h"
#include <functional>
#include <sstream>

Application* Application::m_instance = nullptr;

Application::Application(int argc, char** argv)
   : m_prevInstance(m_instance)
   , m_camera{std::make_shared<Camera>()}
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    m_camera->setWindowSize(glm::ivec2(800, 600));
    glutCreateWindow("CasinoTest");

    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to call glewInit");
    }

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    auto debugCallback = [](GLenum, GLenum type, GLuint, GLenum, GLsizei, const GLchar* message, const void*) {
        if (type == GL_DEBUG_TYPE_ERROR) {
            std::cerr << "OpenGL error: " << message << std::endl;
        }
    };

    glDebugMessageCallback(debugCallback, nullptr);

    m_shaderMgr = std::make_unique<ShaderManager>();

    m_instance = this;

    glutDisplayFunc([]() {
        m_instance->render();
    });
    glutReshapeFunc([](int w, int h) {
        m_instance->setWindowSize(w, h);
    });

    auto image = Image::load("image1.png");
    auto texture = std::make_shared<Texture>(*image.get());

    m_sprite = std::make_unique<Sprite>(texture, std::make_shared<Mesh>(), m_shaderMgr->getSpriteShader());
}

Application::~Application()
{
    glutDisplayFunc(nullptr);
    glutReshapeFunc(nullptr);
    m_instance = m_prevInstance;
}

void Application::render()
{
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glDisable(GL_CULL_FACE);

    m_sprite->draw(m_camera.get());

    glutSwapBuffers();
}

void Application::setWindowSize(int w, int h)
{
    m_camera->setWindowSize(glm::ivec2(w, h));
    glViewport(0, 0, w, h);
}

int Application::run()
{
    glutMainLoop();
    return 0;
}