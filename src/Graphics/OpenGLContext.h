#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct OpenGLContext
{
	void Init()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			std::cout << "Failed to initialize GLAD" << std::endl;
	}

	void PrintInfo()
	{
		std::cout << "OpenGL version: "
			<< glGetString(GL_VERSION) << "\n";

		std::cout << "Renderer: "
			<< glGetString(GL_RENDERER) << "\n";

		std::cout << "Vendor: "
			<< glGetString(GL_VENDOR) << "\n";
	}
};