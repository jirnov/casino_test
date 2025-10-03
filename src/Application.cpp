#include "Application.h"
#include "Camera.h"
#include "FPSMetrics.h"
#include "Game.h"
#include "SpriteManager.h"
//#include <format>

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

    m_spriteMgr = std::make_unique<SpriteManager>();

    m_game = std::make_unique<Game>(*m_spriteMgr);

    registerCallbacks();
}

Application::~Application()
{
    unregisterCallbasks();
}

void Application::render()
{
    glClearColor(1, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_CULL_FACE);

    m_game->render(*m_camera);

    m_metrics->render();

    glutSwapBuffers();
}

void Application::update()
{
    auto curTime = Milliseconds{glutGet(GLUT_ELAPSED_TIME)};
    auto dt = curTime - m_prevTime;
    m_prevTime = curTime;

    m_game->update(dt);

    m_metrics->update(dt);

    glutPostRedisplay();
}

void Application::onKeyboard(unsigned char key)
{
    switch (key) {
        case 27:
            glutLeaveMainLoop();
            break;
        default:
            m_game->onKeyboard(key);
            break;
    }
}

void Application::onMouse(int button, int state, int x, int y)
{
    m_game->onMouse(button, state, x, y);
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

    glutMouseFunc([](int button, int state, int x, int y) {
        if (m_instance) {
            m_instance->onMouse(button, state, x, y);
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
    glutMouseFunc(nullptr);
}
