#include <Windows.h>

#include "InputHandler.h"

void InputHandler::InputLoop()
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD inputRecord;
    DWORD numEvents;

    while (m_Running)
    {
        // 等待输入事件
        if (WaitForSingleObject(hStdin, INFINITE) == WAIT_OBJECT_0)
        {
            if (ReadConsoleInput(hStdin, &inputRecord, 1, &numEvents))
            {
                if (numEvents > 0 && inputRecord.EventType == KEY_EVENT)
                {
                    // 处理键盘事件
                    KEY_EVENT_RECORD& keyEvent = inputRecord.Event.KeyEvent;
                    if (keyEvent.bKeyDown)
                    {
                        KeyPressedEvent event(keyEvent.wVirtualKeyCode);
                        m_Handler(event);
                    }
                    else
                    {
                        KeyReleasedEvent event(keyEvent.wVirtualKeyCode);
                        m_Handler(event);
                    }
                }
            }
        }
    }
}
