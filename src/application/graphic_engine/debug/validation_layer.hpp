#pragma once

#include <vulkan/vulkan.h>

#include <algorithm>
#include <vector>
#include <cstring>

namespace ft
{
	class ValidationLayer
	{

	public:

#ifdef NDEBUG
    	inline static const bool enabled = false;
#else
    	inline static const bool enabled = true;
#endif

		static bool checkSupport()
		{
			uint32_t layerCount;
			vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

			std::vector<VkLayerProperties> availableLayers(layerCount);

			vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

			return std::all_of(m_names.begin(), m_names.end(),
				[&availableLayers](const char* name)
				{
					return std::any_of(availableLayers.begin(), availableLayers.end(),
						[name](const VkLayerProperties& layer)
						{
							return strcmp(name, layer.layerName) == 0;
						}
					);
				}
			);
		}

		static const char *const * names() { return m_names.data(); }

		static uint32_t count() { return m_names.size(); }

	private:

		inline static const std::vector<const char*> m_names = {
			"VK_LAYER_KHRONOS_validation"
		};
	};
}