#pragma once

#include "State.h"
#include "Core/Tool.h"
#include "Elements/Border.h"
#include "Elements/Snake.h"
#include "Elements/Board.h"
#include "Elements/Fruit.h"

#include <vector>

enum class GameState
{
	Playing, Stopped, Terminal
};

class Game : public State
{
public:
	Game(int mapWidth, int mapHeight);
	~Game(){}

	virtual void OnEvent(Event& event) override;
	void Update() override;
	void Render() override;
protected:
	virtual void GenFruit();
	virtual void JudgeEat();
	virtual void JudgeDead();
protected:
	Border m_Border;
	Board m_Board;
	Board m_Rule;
	Leaderboard m_LeaderBoard;
	Snake m_Snake;
	std::vector<Fruit> m_Fruits;
	GameState m_State;
};