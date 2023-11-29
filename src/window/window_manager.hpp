#pragma once

#include <GLFW/glfw3.h>

#include "window.hpp"

#include <string>
#include <vector>
#include <memory>

namespace ft
{
	class WindowManager
	{

	public:

		/**
		 * @brief Initializes GLFW.
		*/
		WindowManager();

		/**
		 * @brief Terminates GLFW.
		*/
		~WindowManager();

		/**
		 * @brief Creates a window with the given width, height, and title.
		*/
		void createWindow(int width, int height, std::string title);

		/**
		 * @brief Polls events for the window.
		*/
		void pollEvents() const;

		/**
		 * @brief Returns true if the window should close.
		*/
		bool shouldWindowClose() const;

	private:

		Window * m_windows = nullptr;
	};
}