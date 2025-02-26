#include <random>
#include <algorithm>
#include <vector>

#include "Application.h"
#include "Core/Tool.h"

#include "Game.h"
#include "Menu.h"

static const std::string rule =
"暂停中\n\n"
"WASD 上下左右\n"
"P 暂停\n"
"C 继续游戏\n"
"R 重新开始\n"
"esc 返回菜单\n"
"蛇头吃到果实则加分\n"
"蛇头撞到身体或墙游戏结束\n";

Game::Game(int mapWidth, int mapHeight)
	:m_Border(mapWidth, mapHeight, "墙", { 0, 0 }), m_Snake(Coord{ mapWidth / 2, mapHeight / 2 }, Direction::Up, 6),
	m_State(GameState::Playing), m_Board(10, 10, Coord{ 4 + mapWidth, 0 }, "计分板: " + std::to_string(6)),
	m_Rule(14, 14, Coord{ 2 + mapWidth, 10 }, rule, " "),
	m_LeaderBoard("C:/Users/Summer/Desktop/程序设计/LeaderBoard.txt", 10, 20, Coord{16 + mapWidth, 0}, "", "榜")
{
	m_Board.Show();
	m_Rule.Hide();
}

void Game::OnEvent(Event& event)
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
				Application::GetInstance().SetState(new Game(20, 20));
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
				Application::GetInstance().SetState(new Game(20, 20));
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

void Game::Update()
{
	switch (m_State)
	{
	case GameState::Playing:
	{
		if (m_Fruits.size() <= 5 && Probility(FruitProbability))
		{
			GenFruit();
		}
		JudgeEat();
		JudgeDead();
		m_Snake.Update();
		break;
	}
	case GameState::Stopped:
	{
		break;
	}
	case GameState::Terminal:
	{
		break;
	}
	}
}

void Game::Render()
{
	m_LeaderBoard.Render();
	switch (m_State)
	{
	case GameState::Playing:
	{
		m_Snake.Render();
		m_Board.Render();
		m_Rule.Render();
		break;
	}
	case GameState::Stopped:
	{
		m_Rule.Render();
		break;
	}
	case GameState::Terminal:
	{
		break;
	}
	}
	
}

void Game::GenFruit()
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
		
		for (auto const& seg : m_Snake.GetBody())
		{
			if (seg == c)
			{
				choosing = true;
				break;
			}
		}
		for (auto const& fruit : m_Fruits)
		{
			if (fruit.GetPosition() == c)
			{
				choosing = true;
				break;
			}
		}
	}
	int score = scoreDist(gen);
	m_Fruits.push_back(Fruit(c, score));
}

void Game::JudgeEat()
{
	Coord head = m_Snake.GetBody()[0];
	auto it = std::find_if(m_Fruits.begin(), m_Fruits.end(), [head](Fruit f) {
		return f.GetPosition() == head;
		});
	if (it != m_Fruits.end())
	{
		m_Snake.Grow(it->GetScore());
		std::string t = "计分板: " + std::to_string(m_Snake.GetBody().size() + it->GetScore());
		m_Fruits.erase(it);
		m_Board.SetText(t);
	}
}

void Game::JudgeDead()
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
		m_LeaderBoard.Insert(m_Snake.GetBody().size());
	}
	else if (std::find_if(++m_Snake.GetBody().begin(), m_Snake.GetBody().end(), [head](Coord const& seg) {
		return seg == head;
		}) != m_Snake.GetBody().end())
	{
		m_Snake.Die();
		Render();
		m_State = GameState::Terminal;
		m_LeaderBoard.Insert(m_Snake.GetBody().size());
	}
}
