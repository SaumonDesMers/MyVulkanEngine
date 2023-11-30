#include "debug_messenger.hpp"
#include "logger.hpp"
#include "validation_layer.hpp"
#include "error.hpp"

namespace ft
{
	static VkResult createDebugUtilsMessengerEXT(
		VkInstance instance,
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkDebugUtilsMessengerEXT* pDebugMessenger
	) {
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
		} else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	static void destroyDebugUtilsMessengerEXT(
		VkInstance instance,
		VkDebugUtilsMessengerEXT debugMessenger,
		const VkAllocationCallbacks* pAllocator
	) {
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr) {
			func(instance, debugMessenger, pAllocator);
		}
	}
	
	DebugMessenger::DebugMessenger(Instance &instance)
		: m_instanceRef(instance)
	{
		if (!ValidationLayer::enabled)
		{
			return;
		}

		setupDebugMessenger();
	}

	DebugMessenger::~DebugMessenger()
	{
		destroyDebugMessenger();
	}

	void DebugMessenger::getCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo)
	{
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

		createInfo.messageSeverity =
			// VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
			// VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

		createInfo.messageType =
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

		createInfo.pfnUserCallback = callback;
		createInfo.pUserData = nullptr;
	}

	void DebugMessenger::setupDebugMessenger()
	{
		VkDebugUtilsMessengerCreateInfoEXT createInfo{};
		getCreateInfo(createInfo);

		CHECK_VK_RESULT(
			createDebugUtilsMessengerEXT(
				m_instanceRef.vkInstance(),
				&createInfo,
				nullptr,
				&m_debugMessenger
			),
			"Failed to set up debug messenger"
		);

		LOG_DEBUG("Debug messenger set up");
	}

	void DebugMessenger::destroyDebugMessenger()
	{
		if (!ValidationLayer::enabled)
		{
			return;
		}

		destroyDebugUtilsMessengerEXT(
			m_instanceRef.vkInstance(),
			m_debugMessenger,
			nullptr
		);

		LOG_DEBUG("Debug messenger destroyed");
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL DebugMessenger::callback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData
	)
	{
		(void) pUserData;

		Logger::Level level;
		switch (messageSeverity)
		{
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			level = Logger::Level::DEBUG;
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			level = Logger::Level::INFO;
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			level = Logger::Level::WARNING;
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			level = Logger::Level::ERROR;
			break;
		default:
			level = Logger::Level::DEBUG;
			break;
		}

		std::string msgType;
		switch (messageType)
		{
		case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
			msgType = "GENERAL";
			break;
		case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
			msgType = "VALIDATION";
			break;
		case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
			msgType = "PERFORMANCE";
			break;
		}

		log << level << "Vulkan \e[4m" << msgType << "\e[0m layer: " << pCallbackData->pMessage << std::endl;

		return VK_FALSE;
	}
}