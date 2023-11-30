#pragma once

#include "instance.hpp"
#include "debug_messenger.hpp"
#include "physical_device.hpp"
#include "device.hpp"
#include "queue.hpp"

#include <vulkan/vulkan.h>

namespace ft
{
	class GraphicEngine
	{

	public:

		GraphicEngine();
		~GraphicEngine();

		GraphicEngine(const GraphicEngine&) = delete;
		GraphicEngine& operator=(const GraphicEngine&) = delete;

	private:

		Instance m_instance;
		DebugMessenger m_debugMessenger;
		PhysicalDevice m_physicalDevice;
		Device m_device;
		Queue m_graphicsQueue;

	};
}
