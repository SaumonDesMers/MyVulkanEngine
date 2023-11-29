#include "instance.hpp"
#include "window_manager.hpp"
#include "error.hpp"

#include <stdexcept>

namespace ft
{
	Instance::Instance()
	{
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "MyVulkanApp";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "MyVulkanEngine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		// uint32_t windowManagerExtensionCount = 0;
		// const char** windowManagerExtensions;

		// windowManagerExtensions = WindowManager::getRequiredInstanceExtensions(&windowManagerExtensionCount);

		// createInfo.enabledExtensionCount = windowManagerExtensionCount;
		// createInfo.ppEnabledExtensionNames = windowManagerExtensions;
		createInfo.ppEnabledExtensionNames = WindowManager::getRequiredInstanceExtensions(&createInfo.enabledExtensionCount);

		createInfo.enabledLayerCount = 0;

		CHECK_VK_RESULT(
			vkCreateInstance(&createInfo, nullptr, &m_instance),
			"Failed to create instance"
		);

		LOG_DEBUG("Instance created");
		
	}

	Instance::~Instance()
	{
		vkDestroyInstance(m_instance, nullptr);
		LOG_DEBUG("Instance destroyed");
	}

	const std::vector<VkExtensionProperties>& Instance::getAvailableExtensions()
	{
		if (m_availableExtensions.empty())
		{
			uint32_t extensionCount = 0;
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

			m_availableExtensions.resize(extensionCount);

			vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, m_availableExtensions.data());

			LOG_INFO("Available extensions:");
			for (const auto& extension : m_availableExtensions)
			{
				LOG_INFO("\t" + std::string(extension.extensionName));
			}
		}

		return m_availableExtensions;
	}
}