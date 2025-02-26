#pragma once

#include <functional>


// 目前只需处理键盘的输入
enum class EventType
{
	KeyPressedEvent, KeyReleasedEvent
};

#define EVENT_FUNCTION(type) \
public: \
static EventType GetStaticType() { return EventType::##type; } \
virtual EventType GetType() const { return GetStaticType(); } \

class Event
{
public:
	Event() = default;
	virtual ~Event() {};
	virtual EventType GetType() const = 0;
};

class KeyPressedEvent : public Event
{
	EVENT_FUNCTION(KeyPressedEvent);
public:
	KeyPressedEvent(int keyCode) : m_KeyCode(keyCode){}
	int GetKeyCode() const { return m_KeyCode; }
private:
	int m_KeyCode;
};

class KeyReleasedEvent : public Event
{
	EVENT_FUNCTION(KeyReleasedEvent);
public:
	KeyReleasedEvent(int keyCode) : m_KeyCode(keyCode) {}
	int GetKeyCode() const { return m_KeyCode; }
private:
	int m_KeyCode;
};

class EventDispatcher
{
public:
	EventDispatcher(Event& event) : m_Event(event) {}

	template<typename T>
	void Dispatch(std::function<void(T&)> func)
	{
		if (m_Event.GetType() == T::GetStaticType())
		{
			func(*((T*)&m_Event));
		}
	}

private:
	Event& m_Event;
};

