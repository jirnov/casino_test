#include "Application.h"
#include "Camera.h"
#include "FPSMetrics.h"
#include "Game.h"
#include "SpriteManager.h"

namespace {
constexpr glm::uvec2 DEFAULT_WINDOW_SIZE{800, 600};
}

Application::Application(int argc, char** argv)
   : m_camera{std::make_shared<Camera>(DEFAULT_WINDOW_SIZE)}
   , m_metrics{std::make_unique<FPSMetrics>()}
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(DEFAULT_WINDOW_SIZE.x, DEFAULT_WINDOW_SIZE.y);
    glutCreateWindow("CasinoTest. SPACE - run wheels, ESC - exit program");

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

    m_glutCallbacks = std::make_unique<GlutCallbacks>(this);
}

Application::~Application()
{}

int Application::run()
{
    glutMainLoop();
    return 0;
}

void Application::onMouseEvent(const MouseEvent& event)
{
    m_game->onMouseEvent(event);
}

void Application::onKeyboardEvent(const KeyboardEvent& event)
{
    switch (event.code) {
        case KeyCode::Escape:
            glutLeaveMainLoop();
            break;
        default:
            m_game->onKeyboardEvent(event);
            break;
    }
}

void Application::onReshapeEvent(const ReshapeEvent& event)
{
    if (event.windowSize != DEFAULT_WINDOW_SIZE) {
        glutReshapeWindow(DEFAULT_WINDOW_SIZE.x, DEFAULT_WINDOW_SIZE.y);

    } else {
        m_camera->setWindowSize(event.windowSize);
        glViewport(0, 0, event.windowSize.x, event.windowSize.y);
    }
}

void Application::onDisplayEvent(const DisplayEvent& event)
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_CULL_FACE);

    m_game->render(*m_camera);

    m_metrics->render();
}

void Application::onTimerEvent(const TimerEvent& event)
{
    m_game->update(event.deltaTime);
    m_metrics->update(event.deltaTime);
}
