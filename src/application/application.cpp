#include "application.hpp"
#include "logger.hpp"
#include "error.hpp"

#include <glm/glm.hpp>

namespace ft
{
	Application::Application()
	{
		m_instance.getAvailableExtensions();
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		m_windowManager.createWindow(800, 600, "MyVulkanEngine");
		mainLoop();
	}

	void Application::mainLoop()
	{
		while (!m_windowManager.shouldWindowClose())
		{
			m_windowManager.pollEvents();
		}

		LOG_DEBUG("Main loop exited");
	}
}