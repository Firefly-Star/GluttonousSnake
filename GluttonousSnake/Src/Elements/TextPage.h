#pragma once

#include <string>

#include "Core/Macros.h"
#include "Element.h"

class TextPage : public Element
{
public:
	TextPage(const std::string& text);
	virtual ~TextPage() override;
	virtual void OnEvent(Event& event) override;
	virtual void Update() override;
	virtual void Render() override;
private:
	const std::string m_Text;
};