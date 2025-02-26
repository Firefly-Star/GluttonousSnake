#pragma once

#include "Border.h"

#include <set>

class Board : public Element
{
public:
	Board(int width, int height, Coord position, std::string text = "", std::string boarderText = "°å");
	void Render() override;
	void SetText(std::string text) { m_Refreshed = true; m_Text = text; }
	void Hide() { m_Refreshed = true; m_Hidden = true; }
	void Show() { m_Refreshed = true; m_Hidden = false; }
private:
	Border m_Border;
	std::string m_Text;
	bool m_Refreshed;
	bool m_Hidden;
};

class Leaderboard : public Element
{
public:
	Leaderboard(const std::string& file, int width, int height, Coord position, std::string text = "", std::string boarderText = "°å");
	void Insert(int score);
	void Render() override;
private:
	std::multiset<int, std::greater<int>> m_Scores;
	std::string m_FileName;
	Board m_Board;
	bool m_Refreshed;
};