#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

struct WindowConfig
{
	std::string title;
	uint32_t width;
	uint32_t height;
	bool vSyncEnabled;
};

class Window
{
public:
	Window(const WindowConfig& config);
	~Window();

	GLFWwindow* GetHandle() { return m_Handle; }

	uint32_t GetWidth() const { return m_Width; }
	uint32_t GetHeight() const { return m_Height; }

	void SetVSync(bool enable);

	void Update();
	bool IsOpened();

private:
	void SetWindowCallbacks();

private:
	GLFWwindow* m_Handle = nullptr;
	uint32_t m_Width = 0;
	uint32_t m_Height = 0;
};
