#pragma once

#include "Forward.h"

struct IEventVisitor {
    virtual ~IEventVisitor() = default;

    virtual void visit(const struct MouseEvent&) = 0;
    virtual void visit(const struct KeyboardEvent&) = 0;
    virtual void visit(const struct ReshapeEvent&) = 0;
    virtual void visit(const struct TimerEvent&) = 0;
    virtual void visit(const struct DisplayEvent&) = 0;
};

struct IEvent {
    virtual ~IEvent() = default;
    virtual void accept(IEventVisitor& visitor) const = 0;
};

enum class MouseButton : int { Unknown = 0, Left, Right, Middle };
enum class MouseState : int { Unknown = 0, Up, Down };

struct MouseEvent : IEvent {
    const MouseButton button;
    const MouseState state;
    const glm::ivec2 pos;

    MouseEvent(MouseButton button, MouseState state, const glm::ivec2& pos)
       : button{button}
       , state{state}
       , pos{pos}
    {}

    void accept(IEventVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

enum class KeyCode : int { Unknown = 0, Escape, Space };

struct KeyboardEvent : IEvent {
    const KeyCode code;

    KeyboardEvent(KeyCode code)
       : code{code}
    {}

    void accept(IEventVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

struct TimerEvent : IEvent {
    Milliseconds deltaTime;

    TimerEvent(const Milliseconds& deltaTime)
       : deltaTime{deltaTime}
    {}

    void accept(IEventVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

struct DisplayEvent : IEvent {
    void accept(IEventVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

struct ReshapeEvent : IEvent {
    const glm::uvec2 windowSize;

    ReshapeEvent(const glm::uvec2& windowSize)
       : windowSize{windowSize}
    {}

    void accept(IEventVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

struct EventListener : IEventVisitor {
    virtual ~EventListener() = default;

    void onEvent(const IEvent& event)
    {
        event.accept(*this);
    }

    void visit(const MouseEvent& event) override
    {
        onMouseEvent(event);
    }

    void visit(const KeyboardEvent& event) override
    {
        onKeyboardEvent(event);
    }

    void visit(const ReshapeEvent& event) override
    {
        onReshapeEvent(event);
    }

    void visit(const TimerEvent& event) override
    {
        onTimerEvent(event);
    }

    void visit(const DisplayEvent& event) override
    {
        onDisplayEvent(event);
    }

protected:
    virtual void onMouseEvent(const MouseEvent& event)
    {}
    virtual void onKeyboardEvent(const KeyboardEvent& event)
    {}
    virtual void onReshapeEvent(const ReshapeEvent& event)
    {}
    virtual void onTimerEvent(const TimerEvent& event)
    {}
    virtual void onDisplayEvent(const DisplayEvent& event)
    {}
};

class GlutCallbacks {
public:
    GlutCallbacks(EventListener* listener, int fps = 1000);
    ~GlutCallbacks();

private:
    void displayFunc();
    void reshapeFunc(int w, int h);
    void timerFunc(int fps);
    void mouseFunc(int button, int state, int x, int y);
    void keyboardFunc(unsigned char key);

    GlutCallbacks* m_prevInstance{nullptr};
    EventListener* m_listener{nullptr};

    Milliseconds m_prevTime;
};
