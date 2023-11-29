#include "window_manager.hpp"
#include "logger.hpp"

#include <stdexcept>
#include <algorithm>

namespace ft
{
	
	WindowManager::WindowManager()
	{
		if (glfwInit() == GLFW_FALSE)
		{
			throw std::runtime_error("Failed to initialize GLFW");
		}
		LOG_DEBUG("GLFW initialized");
	}

	WindowManager::~WindowManager()
	{
		delete m_windows;
		glfwTerminate();
		LOG_DEBUG("GLFW terminated");
	}

	void WindowManager::createWindow(int width, int height, std::string title)
	{
		m_windows = new Window(width, height, title);
	}

	void WindowManager::pollEvents() const
	{
		glfwPollEvents();
	}

	bool WindowManager::shouldWindowClose() const
	{
		return m_windows == nullptr || m_windows->shouldClose();
	}
}