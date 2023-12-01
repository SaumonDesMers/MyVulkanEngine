#include "surface.hpp"

namespace ft
{
	Surface::Surface(GLFWwindow *window, Instance &instance)
		: m_surface(VK_NULL_HANDLE),
		m_instanceRef(instance)
	{
		if (glfwCreateWindowSurface(m_instanceRef.vkInstance(), window, nullptr, &m_surface) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create window surface!");
		}
	}

	Surface::~Surface()
	{
		vkDestroySurfaceKHR(m_instanceRef.vkInstance(), m_surface, nullptr);
	}

}