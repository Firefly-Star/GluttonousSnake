#pragma once

#include "Core/Event.h"
#include "Elements/Element.h"

class State 
{
public:
    virtual ~State() = default;
    virtual void OnEvent(Event& event) {}
    virtual void Update() {}
    virtual void Render() {}
protected:
    State() = default;
};