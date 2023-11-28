#pragma once

#include <GLFW/glfw3.h>

#include "window.hpp"

#include <string>

namespace ft
{
	class WindowManager
	{
	public:
		WindowManager();
		~WindowManager();

		Window createWindow(int width, int height, std::string title);

	private:
	};
}