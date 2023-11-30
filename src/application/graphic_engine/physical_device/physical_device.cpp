#include "physical_device.hpp"
#include "error.hpp"
#include "logger.hpp"
#include "queue.hpp"

#include <map>

namespace ft
{
	PhysicalDevice::PhysicalDevice(Instance &instance)
	{
		std::vector<VkPhysicalDevice> physicalDevices;
		getPhysicalDevices(instance, physicalDevices);
		pickPhysicalDevice(physicalDevices);
	}

	PhysicalDevice::~PhysicalDevice()
	{
		
	}

	void PhysicalDevice::getPhysicalDevices(
		Instance &instance,
		std::vector<VkPhysicalDevice> &physicalDevices
	) const
	{
		uint32_t physicalDeviceCount = 0;
		vkEnumeratePhysicalDevices(instance.vkInstance(), &physicalDeviceCount, nullptr);

		if (physicalDeviceCount == 0)
		{
			throw std::runtime_error("Failed to find GPUs with Vulkan support");
		}

		physicalDevices.clear();
		physicalDevices.resize(physicalDeviceCount);
		vkEnumeratePhysicalDevices(instance.vkInstance(), &physicalDeviceCount, physicalDevices.data());
	}

	void PhysicalDevice::pickPhysicalDevice(std::vector<VkPhysicalDevice> &physicalDevices)
	{
		std::multimap<int, VkPhysicalDevice> candidates;

		for (const auto& device : physicalDevices)
		{
			int score = rateDeviceSuitability(device);
			candidates.insert(std::make_pair(score, device));
		}

		if (candidates.rbegin()->first > 0)
		{
			m_physicalDevice = candidates.rbegin()->second;
		}
		else
		{
			throw std::runtime_error("Failed to find a suitable GPU");
		}
	}

	int PhysicalDevice::rateDeviceSuitability(VkPhysicalDevice device) const
	{
		Queue::FamilyIndices indices = Queue::FamilyIndices::find(device);

		return indices.isComplete() ? 1 : 0;
	}

}