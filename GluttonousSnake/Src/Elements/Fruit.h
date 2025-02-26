#pragma once

#include "core/Tool.h"
#include "Element.h"

class Fruit : public Element
{
public:
	Fruit(Coord position, int score = 1);
	int GetScore() const { return m_Score; }
	Coord GetPosition() const { return m_Position; }
private:
	Coord m_Position;
	int m_Score;
};