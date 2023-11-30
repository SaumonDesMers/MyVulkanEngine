#pragma once

#include "instance.hpp"
#include "debug_messenger.hpp"

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

		void run();

	private:

		Instance m_instance;
		DebugMessenger m_debugMessenger;

	};
}
