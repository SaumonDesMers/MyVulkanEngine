#pragma once

#include "instance.hpp"

#include <vulkan/vulkan.h>

#include <vector>

namespace ft
{
	class PhysicalDevice
	{

	public:

		PhysicalDevice(Instance &);
		~PhysicalDevice();

		PhysicalDevice(const PhysicalDevice&) = delete;
		PhysicalDevice& operator=(const PhysicalDevice&) = delete;

		VkPhysicalDevice vkPhysicalDevice() const { return m_physicalDevice; }

	private:

		VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;

		void getPhysicalDevices(Instance &, std::vector<VkPhysicalDevice>&) const;
		void pickPhysicalDevice(std::vector<VkPhysicalDevice>&);
		int rateDeviceSuitability(VkPhysicalDevice) const;

	};
}