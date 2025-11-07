#pragma once

#include "Forward.h"

enum class MouseButton : int { Unknown = 0, Left, Right, Middle };
enum class MouseState : int { Unknown = 0, Up, Down };
enum class KeyCode : int { Unknown = 0, Escape, Space };

struct IMouseListener {
    virtual ~IMouseListener() = default;
    virtual void onMouse(MouseButton button, MouseState state, const glm::ivec2& pos) = 0;
};

struct IKeyboardListener {
    virtual ~IKeyboardListener() = default;
    virtual void onKeyboard(KeyCode keyCode) = 0;
};

struct IDisplayListener {
    virtual ~IDisplayListener() = default;
    virtual void onRender() = 0;
};

struct ITimerListener {
    virtual ~ITimerListener() = default;
    virtual void onTimer(const Milliseconds& dt) = 0;
};

struct IReshapeListener {
    virtual ~IReshapeListener() = default;
    virtual void onReshape(const glm::uvec2& windowSize) = 0;
};

class GlutCallbacks {
public:
    GlutCallbacks(int fps = 1000);
    ~GlutCallbacks();

    void setMouseListener(IMouseListener* listener);
    void setKeyboardListener(IKeyboardListener* listener);
    void setDisplayListener(IDisplayListener* listener);
    void setTimeListener(ITimerListener* listener);
    void setReshapeListener(IReshapeListener* listener);

private:
    void displayFunc();
    void reshapeFunc(int w, int h);
    void timerFunc(int fps);
    void mouseFunc(int button, int state, int x, int y);
    void keyboardFunc(unsigned char key);

    GlutCallbacks* m_prevInstance{nullptr};

    IMouseListener* m_mouseListener{nullptr};
    IKeyboardListener* m_keyboardListener{nullptr};
    IDisplayListener* m_displayListener{nullptr};
    ITimerListener* m_timerListener{nullptr};
    IReshapeListener* m_reshapeListener{nullptr};

    Milliseconds m_prevTime{Milliseconds::zero()};
};
