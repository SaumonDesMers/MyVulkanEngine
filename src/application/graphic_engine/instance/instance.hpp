#pragma once

#include "error.hpp"

#include <vulkan/vulkan.h>

#include <vector>

namespace ft
{

	class Instance
	{

	public:

		Instance();
		~Instance();

		Instance(const Instance&) = delete;
		Instance& operator=(const Instance&) = delete;

		VkInstance vkInstance() const { return m_instance; }
	
	private:

		VkInstance m_instance;

		void init();

		std::vector<VkExtensionProperties> getAvailableExtensions();
		std::vector<const char*> getRequiredExtensions();

		void logExtensions();

	};
}
