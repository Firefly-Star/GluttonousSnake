#include "Border.h"

Border::Border(int width, int height, std::string const& text, Coord position)
	: m_Width(width), m_Height(height), m_Poisition(position)
{
	Coord coord;
	coord.x = position.x;
	coord.y = position.y;
	for (; coord.x < width + position.x; ++coord.x)
	{
		Print(text, coord);
	}
	coord.x = position.x;
	coord.y = position.y + 1;
	for (; coord.y < height - 1 + position.y; ++coord.y)
	{
		Print(text, coord);
	}
	coord.x = width - 1 + position.x;
	coord.y = 1 + position.y;
	for (; coord.y < height - 1 + position.y; ++coord.y)
	{
		Print(text, coord);
	}
	coord.x = position.x;
	coord.y = height - 1 + position.y;
	for (; coord.x < width + position.x; ++coord.x)
	{
		Print(text, coord);
	}
}