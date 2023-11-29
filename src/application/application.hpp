#pragma once

#include "window_manager.hpp"
#include "instance.hpp"

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
		Instance m_instance;

		void mainLoop();
	};
}