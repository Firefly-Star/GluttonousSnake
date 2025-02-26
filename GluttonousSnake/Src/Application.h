#pragma once

#include "Core/Macros.h"
#include "Core/InputHandler.h"
#include "States/State.h"

class Application
{
	SINGLETON(Application);
public:
	void Start() { m_Running = true; }
	void Run();
	void Stop() { m_Running = false; }

	void SetState(State* state);
private:
	Application();
	~Application();

	void OnEvent(Event& event);
private:
	std::unique_ptr<State> m_State;
	InputHandler m_InputHandler;
	bool m_Running;
};