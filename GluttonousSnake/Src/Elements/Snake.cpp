#include "Snake.h"

#include <iostream>
#include <Windows.h>
#include <optional>
#include <algorithm>
#include <iterator>

inline static const Coord DirectionToCoord(Direction d)
{
	switch (d)
	{
	case Direction::Up: return { 0, -1 };
	case Direction::Down: return { 0, 1 };
	case Direction::Left: return { -1, 0 };
	case Direction::Right: return { 1, 0 };
	default: return { 0, 0 };
	}
}

inline static const std::optional<Direction> KeyToDirection(char c)
{
	switch (c)
	{
	case 'A': return Direction::Left;
	case 'S': return Direction::Down;
	case 'D': return Direction::Right;
	case 'W': return Direction::Up;
	default: return std::nullopt;
	}
}

Snake::Snake(Coord position, Direction direction, int length)
	: m_Direction(direction), m_NextDirection(direction), m_CycleLength(10), m_TickCounter(0), m_WaitToGrow(0), m_Dead(false)
{
	Coord d = DirectionToCoord(direction);
	for (int i = 0; i < length; ++i)
	{
		m_Body.push_back(position);
		position.x -= d.x;
		position.y -= d.y;
	}
}


void Snake::OnEvent(Event& event)
{
	/*if (!m_Dead)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& event) {
			if (KeyToDirection(event.GetKeyCode()).has_value())
			{
				auto d = KeyToDirection(event.GetKeyCode()).value();
				Turn(d);
			}
			});
	}*/
}

void Snake::Update()
{
	if (!m_Dead)
	{
		++m_TickCounter;
		char keyCode = 0;
		if (GetAsyncKeyState('A'))
		{
			keyCode = 'A';
		}
		else if (GetAsyncKeyState('D'))
		{
			keyCode = 'D';
		}
		else if (GetAsyncKeyState('W'))
		{
			keyCode = 'W';
		}
		else if (GetAsyncKeyState('S'))
		{
			keyCode = 'S';
		}
		if (KeyToDirection(keyCode).has_value())
		{
			auto d = KeyToDirection(keyCode).value();
			Turn(d);
		}
		if (m_TickCounter >= m_CycleLength)
		{
			m_TickCounter = 0;
			m_Direction = m_NextDirection;
			Coord next = DirectionToCoord(m_Direction);
			Coord newHead = { m_Body[0].x + next.x, m_Body[0].y + next.y };
			m_Body.insert(m_Body.begin(), newHead);
			if (m_WaitToGrow > 0)
			{
				--m_WaitToGrow;
			}
			else
			{
				m_BodyToBeErased.push_back(*(--m_Body.end()));
				m_Body.pop_back();
			}
		}
		m_CycleLength = max(3, 11 - static_cast<int>(m_Body.size() / 5));
	}
}

void Snake::Render()
{
	if (!m_Dead)
	{
		for (auto const& seg : m_BodyToBeErased)
		{
			Print(" ", seg);
		}
		m_BodyToBeErased.clear();
		Print("Í·", m_Body[0]);
		for (int i = 1; i < m_Body.size(); ++i)
		{
			Print("Éí", m_Body[i]);
		}
	}
	else
	{
		for (auto const& seg : m_Body)
		{
			Print("ËÀ", seg);
		}
	}
}

void Snake::CutOff(std::vector<Coord>::const_iterator it)
{
	auto it2 = it;
	for (; it != m_Body.end(); ++it)
	{
		m_BodyToBeErased.push_back(*it);
	}
	m_Body.erase(it2, m_Body.end());
}

void Snake::Turn(Direction d)
{
	switch (m_Direction)
	{
	case Direction::Up: 
	case Direction::Down:
	{
		if (d == Direction::Left || d == Direction::Right)
			m_NextDirection = d;
		break;
	}
	case Direction::Left:
	case Direction::Right:
	{
		if (d == Direction::Up || d == Direction::Down)
			m_NextDirection = d;
		break;
	}
	}
}
