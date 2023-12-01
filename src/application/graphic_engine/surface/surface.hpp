#pragma once

#include "instance.hpp"

#include <GLFW/glfw3.h>

#include <vulkan/vulkan.h>

namespace ft
{
	class Surface
	{

	public:

		Surface(GLFWwindow *, Instance &);
		~Surface();

		VkSurfaceKHR vkSurface() const { return m_surface; }

	private:

		VkSurfaceKHR m_surface;

		Instance &m_instanceRef;
	};
}