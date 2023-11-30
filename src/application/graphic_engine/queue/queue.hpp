#pragma once

#include <vulkan/vulkan.h>

#include <optional>

namespace ft
{
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() const
		{
			return graphicsFamily.has_value() && presentFamily.has_value();
		}

		static QueueFamilyIndices find(VkPhysicalDevice);
	};
}