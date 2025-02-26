#pragma once

#include "State.h"
#include "Core/Macros.h"


class Rule : public State
{
public:
	Rule();
	~Rule();
	virtual void OnEvent(Event& event) override;
};