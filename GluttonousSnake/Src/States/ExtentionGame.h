#pragma once

#include <vector>
#include "Game.h"
#include "Elements/Wall.h"

class ExtentionGame1 : public Game
{
public:
	ExtentionGame1(int mapWidth, int mapHeight);
	virtual void OnEvent(Event& event) override;
private:
	virtual void GenFruit() override;
	virtual void JudgeDead() override;
private:
	std::vector<Wall> m_Walls;
};