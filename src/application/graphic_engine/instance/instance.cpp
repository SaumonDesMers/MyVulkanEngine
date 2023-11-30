#include "instance.hpp"
#include "window_manager.hpp"
#include "error.hpp"
#include "validation_layer.hpp"
#include "debug_messenger.hpp"

#include <stdexcept>

namespace ft
{
	Instance::Instance()
	{
		init();
		logExtensions();
	}

	Instance::~Instance()
	{
		vkDestroyInstance(m_instance, nullptr);
		LOG_DEBUG("Instance destroyed");
	}

	void Instance::init()
	{
		if (ValidationLayer::enabled && !ValidationLayer::checkSupport())
		{
			throw std::runtime_error("Validation layers requested, but not available");
		}

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

		std::vector<const char*> extensions = getRequiredExtensions();
		createInfo.enabledExtensionCount = extensions.size();
		createInfo.ppEnabledExtensionNames = extensions.data();

		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
		if (ValidationLayer::enabled)
		{
			createInfo.enabledLayerCount = ValidationLayer::count();
			createInfo.ppEnabledLayerNames = ValidationLayer::names();

			DebugMessenger::getCreateInfo(debugCreateInfo);
			createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
		}
		else
		{
			createInfo.enabledLayerCount = 0;
			createInfo.ppEnabledLayerNames = nullptr;
		}

		CHECK_VK_RESULT(
			vkCreateInstance(&createInfo, nullptr, &m_instance),
			"Failed to create instance"
		);

		LOG_DEBUG("Instance created");
	}

	std::vector<VkExtensionProperties> Instance::getAvailableExtensions()
	{
		std::vector<VkExtensionProperties> availableExtensions;
		
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		availableExtensions.resize(extensionCount);

		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

		return availableExtensions;
	}

	std::vector<const char *> Instance::getRequiredExtensions()
	{
		uint32_t windowManagerExtensionCount = 0;
		const char** windowManagerExtensions;
		windowManagerExtensions = WindowManager::getRequiredInstanceExtensions(&windowManagerExtensionCount);

		std::vector<const char*> extensions(windowManagerExtensions, windowManagerExtensions + windowManagerExtensionCount);

		if (ValidationLayer::enabled)
		{
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return extensions;
	}

	void Instance::logExtensions()
	{
		LOG_INFO("Available extensions:");
		std::vector<VkExtensionProperties> availableExtensions = getAvailableExtensions();
		for (const auto& extension : availableExtensions)
		{
			LOG_INFO("\t" + std::string(extension.extensionName));
		}

		LOG_INFO("Required extensions:");
		std::vector<const char*> requiredExtensions = getRequiredExtensions();
		for (const auto& extension : requiredExtensions)
		{
			LOG_INFO("\t" + std::string(extension));
		}
	}
}