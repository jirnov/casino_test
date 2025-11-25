#include "GlutCallbacks.h"
#include <cassert>

namespace {

KeyCode toKeycode(unsigned char code)
{
    switch (code) {
        case 27:
            return KeyCode::Escape;
        case 32:
            return KeyCode::Space;
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

GlutCallbacks::GlutCallbacks(EventListener& listener, int fps)
   : m_listener{&listener}
   , m_prevTime{Milliseconds(glutGet(GLUT_ELAPSED_TIME))}
{
    glutSetWindowData(this);

    glutDisplayFunc([]() {
        auto instance = static_cast<GlutCallbacks*>(glutGetWindowData());
        if (instance) {
            instance->displayFunc();
        }
    });

    glutReshapeFunc([](int w, int h) {
        auto instance = static_cast<GlutCallbacks*>(glutGetWindowData());
        if (instance) {
            instance->reshapeFunc(w, h);
        }
    });

    glutMouseFunc([](int button, int state, int x, int y) {
        auto instance = static_cast<GlutCallbacks*>(glutGetWindowData());
        if (instance) {
            instance->mouseFunc(button, state, x, y);
        }
    });

    glutKeyboardFunc([](unsigned char key, int, int) {
        auto instance = static_cast<GlutCallbacks*>(glutGetWindowData());
        if (instance) {
            instance->keyboardFunc(key);
        }
    });

    glutTimerFunc(
       1,
       [](int value) {
           auto instance = static_cast<GlutCallbacks*>(glutGetWindowData());
           if (instance) {
               instance->timerFunc(value);
           }
       },
       fps);
}

GlutCallbacks::~GlutCallbacks()
{
    glutSetWindowData(nullptr);

    glutTimerFunc(0, nullptr, 0);
    glutKeyboardFunc(nullptr);
    glutMouseFunc(nullptr);
    glutReshapeFunc(nullptr);
    glutDisplayFunc(nullptr);
}

void GlutCallbacks::displayFunc()
{
    if (m_listener) {
        m_listener->onEvent(DisplayEvent{});
    }
    glutSwapBuffers();
}

void GlutCallbacks::reshapeFunc(int w, int h)
{
    if (m_listener) {
        m_listener->onEvent(ReshapeEvent(glm::uvec2{w, h}));
    }
}

void GlutCallbacks::mouseFunc(int button, int state, int x, int y)
{
    if (m_listener) {
        m_listener->onEvent(MouseEvent(toMouseButton(button), toMouseState(state), {x, y}));
    }
}

void GlutCallbacks::keyboardFunc(unsigned char key)
{
    if (m_listener) {
        m_listener->onEvent(KeyboardEvent(toKeycode(key)));
    }
}

void GlutCallbacks::timerFunc(int fps)
{
    auto curTime = Milliseconds{glutGet(GLUT_ELAPSED_TIME)};
    auto dt = curTime - m_prevTime;
    m_prevTime = curTime;

    if (m_listener) {
        m_listener->onEvent(TimerEvent(dt));
    }

    glutTimerFunc(
       1000 / fps,
       [](int value) {
           auto instance = reinterpret_cast<GlutCallbacks*>(glutGetWindowData());
           if (instance) {
               instance->timerFunc(value);
           }
       },
       fps);

    glutPostRedisplay();
}
