#include "ExtentionGame.h"

#include "Application.h"
#include "Menu.h"

#include <random>

ExtentionGame1::ExtentionGame1(int mapWidth, int mapHeight)
	:Game(mapWidth, mapHeight)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> xDist(1, mapWidth - 2);
	std::uniform_int_distribution<int> yDist(1, mapHeight - 2);

	for (int i = 0; i < 10; ++i)
	{
		bool stopped = false;
		Coord c;
		while (!stopped)
		{
			stopped = true;
			c = { xDist(gen), yDist(gen) };
			for (auto const& wall : m_Walls)
			{
				if (wall.GetPosition() == c)
				{
					stopped = false;
					break;
				}
			}
		}
		m_Walls.emplace_back(Wall(c));
	}
}

void ExtentionGame1::OnEvent(Event& event)
{
	switch (m_State)
	{
	case GameState::Playing:
	{
		EventDispatcher dispatcher(event);
		m_Border.OnEvent(event);
		m_Snake.OnEvent(event);
		dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& event) {
			switch (event.GetKeyCode())
			{
			case VK_ESCAPE:
			{
				ClearScreen();
				Application::GetInstance().SetState(new Menu());
				break;
			}
			case 'P':
			{
				m_State = GameState::Stopped;
				m_Rule.Show();
			}
			}
			});
		break;
	}
	case GameState::Stopped:
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& event) {
			switch (event.GetKeyCode())
			{
			case 'R':
			{
				ClearScreen();
				Application::GetInstance().SetState(new ExtentionGame1(30, 20));
				break;
			}
			case 'C':
			{
				m_State = GameState::Playing;
				m_Rule.Hide();
				break;
			}
			case VK_ESCAPE:
			{
				ClearScreen();
				Application::GetInstance().SetState(new Menu());
				break;
			}
			}
			});
		break;
	}
	case GameState::Terminal:
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& event) {
			switch (event.GetKeyCode())
			{
			case 'R':
			{
				ClearScreen();
				Application::GetInstance().SetState(new ExtentionGame1(30, 20));
				break;
			}
			case VK_ESCAPE:
			{
				ClearScreen();
				Application::GetInstance().SetState(new Menu());
				break;
			}
			}
			});
		break;
	}
	}
}

static const float FruitProbability = 1.0f / 20.0f;

void ExtentionGame1::GenFruit()
{
	static const int width = m_Border.GetWidth();
	static const int height = m_Border.GetHeight();

	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<int> xDist(1 + m_Border.GetPosition().x, width - 2 + m_Border.GetPosition().y);
	static std::uniform_int_distribution<int> yDist(1 + m_Border.GetPosition().x, height - 2 + m_Border.GetPosition().y);
	static std::uniform_int_distribution<int> scoreDist(1, 5);

	bool choosing = true;
	Coord c;
	while (choosing)
	{
		choosing = false;
		c.x = xDist(gen);
		c.y = yDist(gen);

		if (std::find_if(m_Snake.GetBody().begin(), m_Snake.GetBody().end(), [c](Coord const& seg) {
			return seg == c;
			}) != m_Snake.GetBody().end())
		{
			choosing = true;
		}
		else if (std::find_if(m_Fruits.begin(), m_Fruits.end(), [c](Fruit const& fruit) {
			return fruit.GetPosition() == c;
			}) != m_Fruits.end())
		{
			choosing = true;
		}
		else if (std::find_if(m_Walls.begin(), m_Walls.end(), [c](Wall const& wall) {
			return wall.GetPosition() == c;
			}) != m_Walls.end())
		{
			choosing = true;
		}
	}
	int score = scoreDist(gen);
	m_Fruits.push_back(Fruit(c, score));
}

void ExtentionGame1::JudgeDead()
{
	static const int width = m_Border.GetWidth();
	static const int height = m_Border.GetHeight();
	Coord head = m_Snake.GetBody()[0];
	Coord borderPosition = m_Border.GetPosition();

	if (head.x - borderPosition.x == 0 || head.x - borderPosition.x == width - 1
		|| head.y - borderPosition.y == 0 || head.y - borderPosition.y == height - 1)
	{
		m_Snake.Die();
		Render();
		m_State = GameState::Terminal;
		m_LeaderBoard.Insert(m_Snake.GetLength());
	}
	else 
	{
		auto it = std::find_if(
			++m_Snake.GetBody().begin(), m_Snake.GetBody().end(), [head](const Coord& seg) { 
				return seg == head; 
			});

		if (it != m_Snake.GetBody().end()) {
			m_Snake.CutOff(it);
			std::string t = "¼Æ·Ö°å: " + std::to_string(m_Snake.GetBody().size());
			m_Board.SetText(t);
		}
		else if (std::find_if(m_Walls.begin(), m_Walls.end(), [head](Wall const& wall) {
			return wall.GetPosition() == head;
			}) != m_Walls.end())
		{
			m_Snake.Die();
			Render();
			m_State = GameState::Terminal;
			m_LeaderBoard.Insert(m_Snake.GetLength());
		}
	}
		
		
}
