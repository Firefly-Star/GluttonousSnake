#include "Fruit.h"

Fruit::Fruit(Coord position, int score)
	: m_Position(position), m_Score(score)
{
	Print(std::to_string(score), position);
}