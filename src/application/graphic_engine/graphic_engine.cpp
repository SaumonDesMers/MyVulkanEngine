#include "graphic_engine.hpp"

namespace ft
{
	GraphicEngine::GraphicEngine()
		: m_instance(),
		m_debugMessenger(m_instance),
		m_physicalDevice(m_instance),
		m_device(m_physicalDevice),
		m_graphicsQueue(m_device.vkDevice(), Queue::FamilyIndices::find(m_physicalDevice.vkPhysicalDevice()))
	{
	}

	GraphicEngine::~GraphicEngine()
	{
	}

}