#pragma once

#include <GLFW/glfw3.h>
#include "InputCodes.h"

class Input
{
public:
	inline static void Init(GLFWwindow* windowHandle) { m_WindowHandle = windowHandle; }

	inline static const bool IsKeyDown(const int keyCode)
	{
		return glfwGetKey(m_WindowHandle, keyCode) == GLFW_PRESS;
	}

	inline static const bool IsMouseKeyDown(const int keyCode)
	{
		return glfwGetMouseButton(m_WindowHandle, keyCode) == GLFW_PRESS;
	}

	inline static void EnableCursor()
	{
		glfwSetInputMode(m_WindowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	inline static void DisableCursor()
	{
		glfwSetInputMode(m_WindowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	inline static const double GetMousePosX()
	{
		double xPos;
		glfwGetCursorPos(m_WindowHandle, &xPos, nullptr);
		return xPos;
	}

	inline static const double GetMousePosY()
	{
		double yPos;
		glfwGetCursorPos(m_WindowHandle, nullptr, &yPos);
		return yPos;
	}

	inline static void GameLoopStart()
	{
		glfwGetCursorPos(m_WindowHandle, &m_StartPos[0], &m_StartPos[1]);
	}

	inline static void GameLoopEnd()
	{
		glfwGetCursorPos(m_WindowHandle, &m_EndPos[0], &m_EndPos[1]);

		m_MouseDelta[0] = (m_EndPos[0] - m_StartPos[0]);
		m_MouseDelta[1] = (m_EndPos[1] - m_StartPos[1]);
	}

	inline static const float GetMouseDeltaX()
	{
		return m_MouseDelta[0];
	}
	
	inline static const float GetMouseDeltaY()
	{
		return m_MouseDelta[1];
	}

private:
	inline static GLFWwindow* m_WindowHandle = nullptr;
	inline static double m_StartPos[2] = { 0.0, 0.0 };
	inline static double m_EndPos[2] = { 0.0, 0.0 };
	inline static double m_MouseDelta[2] = { 0.0, 0.0 };
};