#pragma once

#include "Element.h"

#include "Core/Tool.h"

class Wall : public Element
{
public:
	Wall(Coord position);
	Coord GetPosition() const { return m_Position; }
private:
	Coord m_Position;
};