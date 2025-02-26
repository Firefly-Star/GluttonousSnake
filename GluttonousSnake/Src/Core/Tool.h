#pragma once

#include <vector>
#include <string>

struct Coord
{
	int x;
	int y;

	bool operator== (Coord const& other) const
	{
		return other.x == this->x && other.y == this->y;
	}
};

// ����Ļָ��λ������һ���ַ�
void Print(const std::string& text, Coord coord);

// ��ȡ����̨���ڵĴ�С
void GetConsoleSize(int& width, int& height);

// �ַ�������Ƭ
std::vector<std::string> SplitString(const std::string& text, const char symbol);

// �ڿ���̨���м��ӡ����
void PrintCenteredText(const std::string& text);

// ��ĳһ��������м��ӡ����
void PrintCenteredText(Coord position, int width, int height, const std::string& text);

// ���ع��
void HideCursor();

// ��ʾ���
void ShowCursor();

// �����������
void DisableInputEcho();

// �����������
void EnableInputEcho();

// ����
void ClearScreen();

void ClearScreen(Coord position, int width, int height);

// ���ʳ���true
bool Probility(float probility);