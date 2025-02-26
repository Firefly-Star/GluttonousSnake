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

// 在屏幕指定位置输入一串字符
void Print(const std::string& text, Coord coord);

// 获取控制台窗口的大小
void GetConsoleSize(int& width, int& height);

// 字符串的切片
std::vector<std::string> SplitString(const std::string& text, const char symbol);

// 在控制台正中间打印文字
void PrintCenteredText(const std::string& text);

// 在某一区域的正中间打印文字
void PrintCenteredText(Coord position, int width, int height, const std::string& text);

// 隐藏光标
void HideCursor();

// 显示光标
void ShowCursor();

// 禁用输入回显
void DisableInputEcho();

// 启用输入回显
void EnableInputEcho();

// 清屏
void ClearScreen();

void ClearScreen(Coord position, int width, int height);

// 概率出现true
bool Probility(float probility);