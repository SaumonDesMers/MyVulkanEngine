#pragma once

#include "logger.hpp"

#include <vulkan/vk_enum_string_helper.h>

#define FULL_ERROR_INFO std::string(__PRETTY_FUNCTION__) + ":" + std::to_string(__LINE__) + ": "
