#pragma once

#include "State.h"
#include "Core/Macros.h"


class Menu : public State
{
public:
	Menu();
	~Menu();
	virtual void OnEvent(Event& event) override;
	virtual void Render() override;
};