#pragma once

#include <Windows.h>
#include <iostream>

#include "Core/Tool.h"
#include "Element.h"

class Border : public Element
{
public:
	Border(int width, int height, std::string const& text, Coord position = {0, 0});
	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
	Coord GetPosition() const { return m_Poisition; }
private:
	int m_Width, m_Height;
	Coord m_Poisition;
};