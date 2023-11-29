#pragma once

#include "window_manager.hpp"

namespace ft
{
	class Application
	{
	public:
		Application();
		~Application();

		void run();
	
	private:

		WindowManager m_windowManager;

		void mainLoop();
	};
}