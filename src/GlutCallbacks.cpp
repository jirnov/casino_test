#include "GlutCallbacks.h"
#include <cassert>

namespace {
static GlutCallbacks* instance;

KeyCode toKeycode(unsigned char code)
{
    switch (code) {
        case static_cast<unsigned char>(KeyCode::Escape):
        case static_cast<unsigned char>(KeyCode::Space):
            return static_cast<KeyCode>(code);
        default:
            return KeyCode::Unknown;
    }
}

MouseButton toMouseButton(int button)
{
    switch (button) {
        case GLUT_LEFT_BUTTON:
            return MouseButton::Left;
        case GLUT_RIGHT_BUTTON:
            return MouseButton::Right;
        case GLUT_MIDDLE_BUTTON:
            return MouseButton::Middle;
        default:
            return MouseButton::Unknown;
    }
}

MouseState toMouseState(int state)
{
    switch (state) {
        case GLUT_UP:
            return MouseState::Up;
        case GLUT_DOWN:
            return MouseState::Down;
        default:
            return MouseState::Unknown;
    }
}
} // namespace

GlutCallbacks::GlutCallbacks(int fps)
   : m_prevInstance{instance}
{
    instance = this;

    glutDisplayFunc([]() {
        if (instance) {
            instance->displayFunc();
        }
    });

    glutReshapeFunc([](int w, int h) {
        if (instance) {
            instance->reshapeFunc(w, h);
        }
    });

    glutMouseFunc([](int button, int state, int x, int y) {
        if (instance) {
            instance->mouseFunc(button, state, x, y);
        }
    });

    glutKeyboardFunc([](unsigned char key, int, int) {
        if (instance) {
            instance->keyboardFunc(key);
        }
    });

    glutTimerFunc(
       1,
       [](int value) {
           if (instance) {
               instance->timerFunc(value);
           }
       },
       fps);
}

GlutCallbacks::~GlutCallbacks()
{
    instance = m_prevInstance;

    glutTimerFunc(0, nullptr, 0);
    glutKeyboardFunc(nullptr);
    glutMouseFunc(nullptr);
    glutReshapeFunc(nullptr);
    glutDisplayFunc(nullptr);
}

void GlutCallbacks::setMouseListener(IMouseListener* listener)
{
    m_mouseListener = listener;
}

void GlutCallbacks::setKeyboardListener(IKeyboardListener* listener)
{
    m_keyboardListener = listener;
}

void GlutCallbacks::setDisplayListener(IDisplayListener* listener)
{
    m_displayListener = listener;
}

void GlutCallbacks::setTimeListener(ITimerListener* listener)
{
    m_timerListener = listener;
}

void GlutCallbacks::setReshapeListner(IReshapeListener* listener)
{
    m_reshapeListener = listener;
}

void GlutCallbacks::displayFunc()
{
    if (m_displayListener) {
        m_displayListener->onRender();
    }
    glutSwapBuffers();
}

void GlutCallbacks::reshapeFunc(int w, int h)
{
    if (m_reshapeListener) {
        m_reshapeListener->onReshape(glm::uvec2{w, h});
    }
}

void GlutCallbacks::mouseFunc(int button, int state, int x, int y)
{
    if (m_mouseListener) {
        m_mouseListener->onMouse(toMouseButton(button), toMouseState(state), {x, y});
    }
}

void GlutCallbacks::keyboardFunc(unsigned char key)
{
    if (m_keyboardListener) {
        m_keyboardListener->onKeyboard(toKeycode(key));
    }
}

void GlutCallbacks::timerFunc(int fps)
{
    auto curTime = Milliseconds{glutGet(GLUT_ELAPSED_TIME)};
    auto dt = curTime - m_prevTime;
    m_prevTime = curTime;

    if (m_timerListener) {
        m_timerListener->onTimer(dt);
    }

    glutTimerFunc(
       1000 / fps,
       [](int value) {
           if (instance) {
               instance->timerFunc(value);
           }
       },
       fps);

    glutPostRedisplay();
}
