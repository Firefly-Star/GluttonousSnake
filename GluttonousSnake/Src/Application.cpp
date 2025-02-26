#include <iostream>

#include "Application.h"
#include "Core/Tool.h"
#include "Core/Tick.h"
#include "States/Menu.h"

std::unique_ptr<Application> Application::s_Instance = nullptr;
std::once_flag Application::s_OnceFlag;

static std::chrono::milliseconds tickLength = std::chrono::milliseconds(50);

Application::Application()
	:m_State(std::make_unique<Menu>()), m_InputHandler(MEMBER_BIND(Application::OnEvent)), m_Running(false)
{
	m_InputHandler.TurnOn();
}

Application::~Application()
{
}

void Application::OnEvent(Event& event)
{
	m_State->OnEvent(event);
}

void Application::Run()
{
	while (m_Running)
	{
		Tick tick;
		m_State->Update();
		m_State->Render();
		tick.WaitFor(tickLength);
	}
}

void Application::SetState(State* state)
{
	m_State.reset(state);
}