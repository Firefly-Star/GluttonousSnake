#include <iostream>

#include "Menu.h"
#include "Rule.h"
#include "Game.h"
#include "Core/Tool.h"
#include "Application.h"

const char* menuText =
"��ӭ����̰����\n\n"
"1. ������Ϸ\n\n"
"2. �鿴����\n\n"
"����������˳���Ϸ";

Menu::Menu()
{
	DisableInputEcho();
	HideCursor();
	PrintCenteredText(menuText);
}

Menu::~Menu()
{
}

void Menu::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);

	dispatcher.Dispatch<KeyPressedEvent>([](KeyPressedEvent& event) {
		switch (event.GetKeyCode())
		{
		case '1':
		{
			ClearScreen();
			Application::GetInstance().SetState(new Game(20, 20)); break;
		}
		case '2': 
		{
			ClearScreen();
			Application::GetInstance().SetState(new Rule()); break;
		}
		default:
		{
			ClearScreen();
			Application::GetInstance().Stop();
		}
		}
		
		});

}

void Menu::Render()
{
}