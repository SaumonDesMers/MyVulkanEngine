#include "queue.hpp"
#include "physical_device.hpp"

#include <vector>

namespace ft
{
	Queue::Queue(VkDevice device, FamilyIndices indices)
	{
		init(device, indices);
	}

	Queue::~Queue()
	{
	}

	void Queue::init(VkDevice device, FamilyIndices indices)
	{
		vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &m_queue);
	}

	Queue::FamilyIndices Queue::FamilyIndices::find(VkPhysicalDevice physicalDevice)
	{
		Queue::FamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(
			physicalDevice,
			&queueFamilyCount,
			nullptr
		);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(
			physicalDevice,
			&queueFamilyCount,
			queueFamilies.data()
		);

		int i = 0;
		for (const auto& queueFamily : queueFamilies)
		{
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				indices.graphicsFamily = i;
			}

			if (indices.isComplete())
			{
				break;
			}

			i++;
		}

		return indices;
	}
}