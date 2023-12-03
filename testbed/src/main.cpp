#include <core/logger.hpp>

#include <cassert>

int main()
{
	FT_CRITICAL("Critical");
	FT_ERROR("Error");
	FT_WARNING("Warning");
	FT_INFO("Info");
	FT_DEBUG("Debug");
	FT_TRACE("Trace");

	return 0;
}