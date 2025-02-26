#pragma once

#include "Element.h"
#include "Core/Tool.h"

class TextBox : public Element
{
public:
	TextBox(Coord position, std::string text);
	void Update() override;
	void Render() override;

	void Hide() { m_Refreshed = true; m_Hidden = true; }
	void Show() { m_Refreshed = true; m_Hidden = false; }
private:
	Coord m_Position;
	const std::string text;
	std::string content;
	bool m_Refreshed;
	bool m_Hidden;
};