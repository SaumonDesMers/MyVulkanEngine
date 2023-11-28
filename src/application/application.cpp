#include "application.hpp"
#include "logger.hpp"

namespace ft
{
	Application::Application()
	{
		log.setTimestamp(false);
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		log << "Application::run()" << std::endl;
		throw std::runtime_error("Application::run() not implemented");
	}
}