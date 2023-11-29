#pragma once

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
	
		const std::vector<VkExtensionProperties>& getAvailableExtensions();
		
	private:

		VkInstance m_instance;

		std::vector<VkExtensionProperties> m_availableExtensions;

	};
}
