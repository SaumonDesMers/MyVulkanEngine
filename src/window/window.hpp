#pragma once

#include <GLFW/glfw3.h>

#include <string>
#include <memory>

namespace ft
{
	class Window
	{
		friend class WindowManager;
	
	public:

		/**
		 * @brief Creates a window with the given width, height, and title.
		*/
		Window(int width, int height, std::string title);

		/**
		 * @brief Destroys the window.
		*/
		~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		/**
		 * @brief Returns true if the window should close.
		*/
		bool shouldClose() const { return glfwWindowShouldClose(m_window) == GLFW_TRUE; }

		/**
		 * @brief Polls events for the window.
		*/
		void pollEvents() const { glfwPollEvents(); }

	private:

		GLFWwindow* m_window;

		std::string m_title;
		int m_width;
		int m_height;

	};
}