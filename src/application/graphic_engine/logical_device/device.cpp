#include "device.hpp"
#include "physical_device.hpp"
#include "validation_layer.hpp"
#include "queue.hpp"
#include "error.hpp"

namespace ft
{
	Device::Device(PhysicalDevice &physicalDevice)
	{
		init(physicalDevice);
	}

	Device::~Device()
	{
		vkDestroyDevice(m_device, nullptr);
	}

	void Device::init(PhysicalDevice &physicalDevice)
	{
		Queue::FamilyIndices indices = Queue::FamilyIndices::find(physicalDevice.vkPhysicalDevice());

		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
		queueCreateInfo.queueCount = 1;

		float queuePriority = 1.0f;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = &queueCreateInfo;
		createInfo.queueCreateInfoCount = 1;
		createInfo.pEnabledFeatures = &deviceFeatures;

		createInfo.enabledExtensionCount = 0;

		if (ValidationLayer::enabled)
		{
			createInfo.enabledLayerCount = ValidationLayer::count();
			createInfo.ppEnabledLayerNames = ValidationLayer::names();
		}
		else
		{
			createInfo.enabledLayerCount = 0;
		}
		(void)createInfo;

		CHECK_VK_RESULT(
			vkCreateDevice(physicalDevice.vkPhysicalDevice(), &createInfo, nullptr, &m_device),
			"Failed to create logical device!"
		)
	}

}