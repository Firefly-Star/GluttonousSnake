#include "Board.h"

#include <stdexcept>
#include <fstream>
#include <sstream>

Board::Board(int width, int height, Coord position, std::string text, std::string borderText)
	:m_Border(width, height, borderText, position), m_Refreshed(true), m_Text(text), m_Hidden(true)
{
	Render();
}

void Board::Render()
{
	if (m_Refreshed)
	{
		ClearScreen(Coord{ m_Border.GetPosition().x + 1, m_Border.GetPosition().y + 1 }, m_Border.GetWidth() - 2, m_Border.GetHeight() - 2);
		if (!m_Hidden)
		{
			PrintCenteredText(m_Border.GetPosition(), m_Border.GetWidth(), m_Border.GetHeight(), m_Text);
		}
		m_Refreshed = false;
	}
}

Leaderboard::Leaderboard(const std::string& fileName, int width, int height, Coord position, std::string text, std::string boarderText)
	: m_Board(width, height, position, text, boarderText), m_FileName(fileName)
{
	m_Board.Show();

	std::ifstream file(fileName);
	if (!file.is_open())
	{
		throw std::runtime_error("Cannot open Leaderboard File!");
	}

	std::string line;
	while (std::getline(file, line))
	{
		int x = static_cast<int>(std::strtol(line.c_str(), nullptr, 0));
		m_Scores.insert(x);
	}
	m_Refreshed = true;
}

void Leaderboard::Insert(int score)
{
	m_Scores.insert(score);
	std::ofstream file(m_FileName, std::ios::app);
	if (!file.is_open())
	{
		throw std::runtime_error("Cannot open Leaderboard File!");
	}
	file << std::to_string(score) << "\n";
	m_Refreshed = true;
}

void Leaderboard::Render()
{
	if (m_Refreshed)
	{
		static int length = 10;
		int counter = 0;
		std::stringstream ss;
		ss << "ÅÅÐÐ°ñ\n\n";
		for (auto score : m_Scores)
		{
			++counter;
			ss << score << "\n";
			if (counter == length)
			{
				break;
			}
		}
		m_Board.SetText(ss.str());
		m_Refreshed = false;
		m_Board.Render();
	}
}