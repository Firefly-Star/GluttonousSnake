#pragma once

#include <memory>
#include <vector>

#include "Core/Event.h"

class Element
{
public:
	virtual ~Element() {}
	virtual void OnEvent(Event& event){}
	virtual void Update(){}
	virtual void Render(){}
protected:
	Element(){}
};

class Elements
{
public:
	Elements() = default;
	~Elements() {}
	void OnEvent(Event& event)
	{
		for (auto& element : elements)
		{
			element->OnEvent(event);
		}
	}
	void Update()
	{
		for (auto& element : elements)
		{
			element->Update();
		}
	}
	void Render()
	{
		for (auto& element : elements)
		{
			element->Render();
		}
	}
	std::vector<std::unique_ptr<Element>> elements;
};