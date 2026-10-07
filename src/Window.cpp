#include "Window.h"

Window::Window(const WindowConfig& config) : m_Width(config.width), m_Height(config.height)
{
	if (!glfwInit()) {
		std::cout << "GLFW failed to initalize!" << '\n';
		return;
	}

	m_Handle = glfwCreateWindow(config.width, config.height, config.title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_Handle);

	SetVSync(config.vSyncEnabled);

	glfwSetWindowUserPointer(m_Handle, this);

	SetWindowCallbacks();
}

void Window::SetWindowCallbacks()
{
	glfwSetFramebufferSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height)
		{
			Window* wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));
			wnd->m_Width = width;
			wnd->m_Height = height;

			glViewport(0, 0, width, height);
		});
}

void Window::Update()
{
	glfwSwapBuffers(m_Handle);
	glfwPollEvents();
}

bool Window::IsOpened()
{
	return !glfwWindowShouldClose(m_Handle);
}

void Window::SetVSync(bool enabled)
{
	if (enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);
}

Window::~Window()
{
	glfwDestroyWindow(m_Handle);
	glfwTerminate();
}
