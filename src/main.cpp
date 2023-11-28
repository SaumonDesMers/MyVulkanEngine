#include <vulkan/vulkan.h>

#include "application.hpp"
#include "logger.hpp"

#include <stdexcept>

int main()
{
	try
	{
		ft::Application app;

		app.run();
	}
	catch(const std::exception& e)
	{
		ft::log << ft::Logger::Level::ERROR << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}