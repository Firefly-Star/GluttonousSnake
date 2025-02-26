#include <iostream>
// #include "WinUser.h"

#include "Elements/TextPage.h"
#include "Rule.h"
#include "Core/Tool.h"
#include "Application.h"
#include "Menu.h"

const char* ruleText =
"贪吃蛇规则:\n\n"
"WASD 上下左右\n"
"P 暂停\n"
"C 继续游戏\n"
"R 重新开始\n"
"esc 返回菜单\n"
"蛇头吃到果实则加分\n"
"蛇头撞到身体或墙游戏结束\n"
"\n"
"按任意键返回菜单";

Rule::Rule()
{
	DisableInputEcho();
	HideCursor();
	PrintCenteredText(ruleText);
}

Rule::~Rule()
{
}

void Rule::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);

	dispatcher.Dispatch<KeyPressedEvent>([](KeyPressedEvent& event) {
		ClearScreen();
		Application::GetInstance().SetState(new Menu());
		});

}