#include "Application.h"
#include "Camera.h"
#include "FPSMetrics.h"
#include "Image.h"
#include "Mesh.h"
#include "ShaderManager.h"
#include "Sprite.h"
#include "Texture.h"
#include "Wheel.h"
#include <format>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

Application* Application::m_instance = nullptr;

Application::Application(int argc, char** argv)
   : m_prevInstance(m_instance)
   , m_camera{std::make_shared<Camera>()}
   , m_metrics{std::make_unique<FPSMetrics>()}
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    m_camera->setWindowSize(glm::ivec2(WINDOW_WIDTH, WINDOW_HEIGHT));
    m_winId = glutCreateWindow("CasinoTest");

    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to call glewInit");
    }

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    auto debugCallback = [](GLenum, GLenum type, GLuint, GLenum, GLsizei, const GLchar* message, const void*) {
        if (type == GL_DEBUG_TYPE_ERROR) {
            auto info = std::format("OpenGL error: {}", message);
            std::cerr << info << std::endl;
        }
    };

    glDebugMessageCallback(debugCallback, nullptr);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_shaderMgr = std::make_unique<ShaderManager>();

    TextureVector textures;
    textures.reserve(7);
    for (int i = 0; i < 7; ++i) {
        auto name = std::format("image{}.png", i + 1);
        auto image = Image::load(name);
        textures.push_back(std::make_shared<Texture>(*image));
    }

    auto mesh = std::make_shared<Mesh>();
    auto shader = m_shaderMgr->getSpriteShader();

    m_wheel = std::make_unique<Wheel>(textures, mesh, shader);

    {
        auto image = Image::load("foreground.png");
        auto tex = std::make_shared<Texture>(*image);

        m_foreground = std::make_unique<Sprite>(tex, mesh, shader);
    }

    registerCallbacks();
}

Application::~Application()
{
    unregisterCallbasks();
}

void Application::render()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glDisable(GL_CULL_FACE);

    m_wheel->draw(*m_camera);
    m_foreground->render(*m_camera);

    m_metrics->render();

    glutSwapBuffers();
}

void Application::update()
{
    auto curTime = Milliseconds{glutGet(GLUT_ELAPSED_TIME)};
    auto deltaTime = curTime - m_prevTime;
    m_prevTime = curTime;

    m_wheel->update(deltaTime);
    m_metrics->update(deltaTime);

    glutPostRedisplay();
}

void Application::onKeyboard(unsigned char key)
{
    switch (key) {
        case 27:
            glutLeaveMainLoop();
            break;
    }
}

void Application::timerFunc(int fps)
{
    if (m_instance) {
        m_instance->update();
    }
    glutTimerFunc(1000 / fps, timerFunc, fps);
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

void Application::registerCallbacks()
{
    m_prevInstance = m_instance;
    m_instance = this;

    glutDisplayFunc([]() {
        if (m_instance) {
            m_instance->render();
        }
    });

    glutReshapeFunc([](int w, int h) {
        if (w != WINDOW_WIDTH || h != WINDOW_HEIGHT) {
            glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
        }
        if (m_instance) {
            m_instance->setWindowSize(w, h);
        }
    });

    glutTimerFunc(1, &Application::timerFunc, 1000);

    glutKeyboardFunc([](unsigned char key, int, int) {
        if (m_instance) {
            m_instance->onKeyboard(key);
        }
    });
}

void Application::unregisterCallbasks()
{
    m_instance = m_prevInstance;

    glutDisplayFunc([]() {});
    glutReshapeFunc(nullptr);
    glutTimerFunc(0, nullptr, 0);
    glutKeyboardFunc(nullptr);
}
