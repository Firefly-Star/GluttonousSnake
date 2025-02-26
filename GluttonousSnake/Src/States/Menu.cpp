#include <iostream>

#include "Menu.h"
#include "Rule.h"
#include "Game.h"
#include "ExtentionGame.h"
#include "Core/Tool.h"
#include "Application.h"

const char* menuText =
"欢迎来到贪吃蛇\n\n"
"1. 进入游戏1\n\n"
"2. 进入游戏2\n\n"
"3. 查看规则\n\n"
"其他任意键退出游戏";

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
			Application::GetInstance().SetState(new Game(30, 20)); break;
		}
		case '2':
		{
			ClearScreen();
			Application::GetInstance().SetState(new ExtentionGame1(30, 20)); break;
		}
		case '3': 
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