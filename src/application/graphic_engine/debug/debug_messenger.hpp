#pragma once

#include "instance.hpp"

#include <vulkan/vulkan.h>

namespace ft
{
	class DebugMessenger
	{

	public:

		DebugMessenger(Instance &instance);
		~DebugMessenger();

		DebugMessenger(const DebugMessenger&) = delete;
		DebugMessenger& operator=(const DebugMessenger&) = delete;

		static void getCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
	
	private:

		Instance &m_instanceRef;
		VkDebugUtilsMessengerEXT m_debugMessenger;

		void setupDebugMessenger();
		void destroyDebugMessenger();

		static VKAPI_ATTR VkBool32 VKAPI_CALL callback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData
		);

	};
}