#include "window_manager.hpp"

#include <stdexcept>

namespace ft
{
	WindowManager::WindowManager()
	{
		if (glfwInit() == GLFW_FALSE)
		{
			throw std::runtime_error("Failed to initialize GLFW");
		}
	}

	WindowManager::~WindowManager()
	{
		glfwTerminate();
	}

	Window WindowManager::createWindow(int width, int height, std::string title)
	{
		return Window(width, height, title);
	}
}