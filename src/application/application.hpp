#pragma once

#include "window_manager.hpp"
#include "graphic_engine.hpp"

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
		GraphicEngine m_graphicEngine;

		void mainLoop();
	};
}