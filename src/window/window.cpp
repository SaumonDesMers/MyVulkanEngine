#include "window.hpp"
#include "logger.hpp"

#include <stdexcept>
#include <memory>

namespace ft
{
	Window::Window(int width, int height, std::string title)
		: m_title(title), m_width(width), m_height(height)
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_window = glfwCreateWindow(m_width, m_height, title.c_str(), nullptr, nullptr);
		if (m_window == nullptr)
		{
			throw std::runtime_error("Failed to create GLFW window");
		}
		LOG_DEBUG("Window '" + m_title + "' created");
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_window);
		LOG_DEBUG("Window '" + m_title + "' destroyed");
	}
}