#pragma once

#include "logger.hpp"

#include <vulkan/vk_enum_string_helper.h>

#define FULL_ERROR_INFO std::string(__PRETTY_FUNCTION__) + ":" + std::to_string(__LINE__) + ": "

#define CHECK_VK_RESULT(result, msg) \
	if (result != VK_SUCCESS) \
	{ \
		throw std::runtime_error(FULL_ERROR_INFO + msg + " [" + string_VkResult(result) + "]"); \
	}
