#pragma once

#include <vector>

#include "Element.h"
#include "Core/Tool.h"

enum class Direction
{
	Up, Down, Left, Right
};

class Snake : public Element
{
public:
	Snake(Coord position, Direction direction = Direction::Right, int length = 3);
	void OnEvent(Event& event) override;
	void Update() override;
	void Render() override;

	void SetCycleLength(int length) { m_CycleLength = length; }
	const std::vector<Coord>& GetBody() const { return m_Body; }
	int GetLength() const { return m_Body.size() + m_WaitToGrow; }
	void Grow(int growth) { m_WaitToGrow += growth; }
	void Die() { m_Dead = true; }
	void CutOff(std::vector<Coord>::const_iterator it);
private:
	std::vector<Coord> m_Body;
	std::vector<Coord> m_BodyToBeErased;
	Direction m_Direction;
	Direction m_NextDirection;
	int m_CycleLength;
	int m_TickCounter;
	int m_WaitToGrow;
	bool m_Dead;
private:
	void Turn(Direction d);
};