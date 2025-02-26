#pragma once

#include <chrono>
#include <stdexcept>
#include <thread>
#include <Windows.h>

class Tick
{
public:
	Tick()
		: m_StartPoint(std::chrono::steady_clock::now())
	{
	}
	// 从Tick对象创建开始计时
	void WaitFor(std::chrono::milliseconds duration)
	{
		auto currentPoint = std::chrono::steady_clock::now();
		std::chrono::milliseconds leftDuration = duration - std::chrono::duration_cast<std::chrono::milliseconds>(currentPoint - m_StartPoint);
		if (leftDuration < std::chrono::milliseconds(0))
		{
			return;//throw std::runtime_error("Frame Drop");
		}
		try {
			std::this_thread::sleep_for(leftDuration);
		}
		catch (std::runtime_error e)
		{
		}
	}
private:
	std::chrono::steady_clock::time_point m_StartPoint;
};