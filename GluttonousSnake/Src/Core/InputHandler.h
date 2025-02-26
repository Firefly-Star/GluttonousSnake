#pragma once

#include <functional>
#include <atomic>
#include <thread>

#include "Event.h"

class InputHandler
{
public:
    InputHandler(std::function<void(Event&)> handler)
        : m_Handler(handler), m_Running(false)
    {
    }
    ~InputHandler()
    {
        TurnOff();
    }
    void TurnOn()
    {
        if (!m_Running)
        {
            m_Running = true;
            m_InputThread = std::thread(&InputHandler::InputLoop, this);
        }
    }
    void TurnOff()
    {
        if (m_Running)
        {
            m_Running = false;
            if (m_InputThread.joinable()) 
            {
                m_InputThread.join();
            }
        }
    }
private:
    void InputLoop();
private:
    std::function<void(Event&)> m_Handler;
    std::atomic<bool> m_Running;
    std::thread m_InputThread;
};