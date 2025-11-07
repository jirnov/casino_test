#include "Application.h"
#include "Camera.h"
#include "FPSMetrics.h"
#include "Game.h"
#include "SpriteManager.h"

namespace {
constexpr glm::uvec2 DEFAULT_WINDOW_SIZE{800, 600};
}

Application::Application(int argc, char** argv)
   : m_camera{std::make_shared<Camera>()}
   , m_metrics{std::make_unique<FPSMetrics>()}
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(DEFAULT_WINDOW_SIZE.x, DEFAULT_WINDOW_SIZE.y);
    m_camera->setWindowSize(DEFAULT_WINDOW_SIZE);
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

    m_glutCallbacks = std::make_unique<GlutCallbacks>();
    m_glutCallbacks->setDisplayListener(this);
    m_glutCallbacks->setKeyboardListener(this);
    m_glutCallbacks->setMouseListener(m_game.get());
    m_glutCallbacks->setReshapeListner(this);
    m_glutCallbacks->setTimeListener(this);
}

Application::~Application()
{}

void Application::onKeyboard(KeyCode code)
{
    switch (code) {
        case KeyCode::Escape:
            glutLeaveMainLoop();
            break;
        default:
            m_game->onKeyboard(code);
            break;
    }
}

void Application::onReshape(const glm::uvec2& windowSize)
{
    if (windowSize != DEFAULT_WINDOW_SIZE) {
        glutReshapeWindow(DEFAULT_WINDOW_SIZE.x, DEFAULT_WINDOW_SIZE.y);

    } else {
        m_camera->setWindowSize(windowSize);
        glViewport(0, 0, windowSize.x, windowSize.y);
    }
}

int Application::run()
{
    glutMainLoop();
    return 0;
}

void Application::onTimer(const Milliseconds& dt)
{
    m_game->update(dt);

    m_metrics->update(dt);
}

void Application::onRender()
{
    glClearColor(1, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_CULL_FACE);

    m_game->render(*m_camera);

    m_metrics->render();
}
