#include "Application.h"

void Application::Init(const WindowConfig& winConfig)
{
	m_Window = std::make_shared<Window>(winConfig);
}

void Application::Run()
{
	OnCreate();
	OnUpdate();
	OnDestroy();
}

void Application::OnCreate()
{
	
}

void Application::OnUpdate()
{
	
}

void Application::OnDestroy()
{
}
