#include <iostream>
// #include "WinUser.h"

#include "Elements/TextPage.h"
#include "Rule.h"
#include "Core/Tool.h"
#include "Application.h"
#include "Menu.h"

const char* ruleText =
"̰���߹���:\n\n"
"WASD ��������\n"
"P ��ͣ\n"
"C ������Ϸ\n"
"R ���¿�ʼ\n"
"esc ���ز˵�\n"
"��ͷ�Ե���ʵ��ӷ�\n"
"��ͷײ�������ǽ��Ϸ����\n"
"\n"
"����������ز˵�";

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