#include <iostream>
#include <Windows.h>
#include <random>
#include <stdexcept>

#include "Tool.h"

void Print(const std::string& text, Coord coord)
{
    COORD c;
    c.X = coord.x * 2;
    c.Y = coord.y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    std::cout << text;
}

void GetConsoleSize(int& width, int& height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

std::vector<std::string> SplitString(const std::string& text, const char symbol)
{
    std::vector<std::string> container;
    std::string workString;
    for (const auto c : text)
    {
        workString.push_back(c);
        if (c == symbol)
        {
            container.push_back(workString);
            workString.clear();
        }
    }
    if (!workString.empty())
    {
        container.push_back(workString);
    }
    return container;
}

void PrintCenteredText(const std::string& text) {
    int consoleWidth, consoleHeight;
    GetConsoleSize(consoleWidth, consoleHeight);
    auto container = SplitString(text, '\n');
    int beginHeight = (consoleHeight - container.size()) / 2;
    for (auto const& line : container)
    {
        COORD coord;
        coord.X = (consoleWidth - line.length()) / 2;
        coord.Y = beginHeight;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        std::cout << line;
        ++beginHeight;
    }
}

void PrintCenteredText(Coord position, int width, int height, const std::string& text)
{
    auto container = SplitString(text, '\n');
    int beginHeight = position.y + (height - container.size()) / 2;
    for (auto const& line : container)
    {
        COORD coord;
        coord.X = (width * 2 - line.length()) / 2 + 2 * position.x;
        coord.Y = beginHeight;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        std::cout << line;
        ++beginHeight;
    }
}

void HideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false; // 设置光标不可见
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void ShowCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = true; // 设置光标可见
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void DisableInputEcho() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & ~ENABLE_ECHO_INPUT); // 禁用回显
}

void EnableInputEcho() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode | ENABLE_ECHO_INPUT); // 启用回显
}

void ClearScreen()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) {
        return;
    }

    // 获取控制台屏幕缓冲区信息
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        return;
    }

    // 计算需要清除的字符数
    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // 填充控制台屏幕缓冲区
    COORD homeCoords = { 0, 0 };
    DWORD count;
    FillConsoleOutputCharacter(hStdOut, ' ', cellCount, homeCoords, &count);
    FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count);

    // 将光标移动到左上角
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

void ClearScreen(Coord _position, int width, int height)
{
    COORD position;
    position.X = _position.x * 2;
    position.Y = _position.y;

    // 计算需要清除的字符数
    for (int i = 0; i < height; ++i)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
        for (int j = 0; j < width * 2; ++j)
        {
            std::cout << " ";
        }
        ++position.Y;
    }

}

bool Probility(float p)
{
    if (p < 0.0f || p > 1.0f)
    {
        throw std::runtime_error("Probability should be between 0.0f and 1.0f!");
    }
    static std::random_device rd;
    static std::mt19937 gen(rd());

    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    float randomFloat = dist(gen);

    return randomFloat < p;
}