#pragma once

#include "Window.h"

class Application
{
public:
	void Init(const WindowConfig& winConfig);
	void Run();

private:
	void OnCreate();
	void OnUpdate();
	void OnDestroy();

	const std::shared_ptr<Window>& getWindow() { return m_Window; }

private:
	std::shared_ptr<Window> m_Window;
};