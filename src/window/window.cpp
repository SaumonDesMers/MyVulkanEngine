#include "window.hpp"

#include <stdexcept>

namespace ft
{
	Window::Window(int width, int height, std::string title)
	{
		m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (m_window == nullptr)
		{
			throw std::runtime_error("Failed to create GLFW window");
		}
	}
}