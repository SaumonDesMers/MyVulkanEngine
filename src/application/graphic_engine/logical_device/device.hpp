#pragma once

#include "physical_device.hpp"

#include <vulkan/vulkan.h>

namespace ft
{
	class Device
	{

	public:

		Device(PhysicalDevice &physicalDevice);
		~Device();

		Device(const Device&) = delete;
		Device& operator=(const Device&) = delete;

		VkDevice vkDevice() const { return m_device; }

	private:

		VkDevice m_device;

		void init(PhysicalDevice &physicalDevice);

	};
}