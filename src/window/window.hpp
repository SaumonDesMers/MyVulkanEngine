#pragma once

#include <GLFW/glfw3.h>

#include <string>

namespace ft
{
	class Window
	{
		friend class WindowManager;
	
	public:

		~Window();

		bool shouldClose() const { return glfwWindowShouldClose(m_window); }
		void pollEvents() const { glfwPollEvents(); }

	private:

		GLFWwindow* m_window;

		Window(int width, int height, std::string title);

	};
}