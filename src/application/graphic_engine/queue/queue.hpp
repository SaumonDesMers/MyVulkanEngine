#pragma once

#include <vulkan/vulkan.h>

#include <optional>

namespace ft
{
	class Queue
	{
	
	public:
		struct FamilyIndices
		{
			std::optional<uint32_t> graphicsFamily;
			// std::optional<uint32_t> presentFamily;

			bool isComplete() const
			{
				// return graphicsFamily.has_value() && presentFamily.has_value();
				return graphicsFamily.has_value();
			}

			static FamilyIndices find(VkPhysicalDevice);
		};

		Queue(VkDevice, FamilyIndices);
		~Queue();
	
	private:

		VkQueue m_queue;

		void init(VkDevice, FamilyIndices);
	};
}