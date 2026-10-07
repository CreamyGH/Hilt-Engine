#pragma once

#include <iostream>
#include <GLFW/glfw3.h>

class TimeStep
{
public:

	inline static const double GetDeltaTime()
	{
		return m_DeltaTime;
	}

	inline static const double GetFPS()
	{
		return 1.0 / m_DeltaTime;
	}

	inline static void GameLoopStart()
	{
		m_StartTime = glfwGetTime();
	}

	inline static void GameLoopEnd()
	{
		m_EndTime = glfwGetTime();
		m_DeltaTime = m_EndTime - m_StartTime;

		if (m_DeltaTime < 0) {
			std::cout << "negative delta time!" << '\n';
			m_DeltaTime = 1.0;
		}
	}

private:
	inline static double m_StartTime = 0.0;
	inline static double m_EndTime = 0.0;
	inline static double m_DeltaTime = 1.0;
};
