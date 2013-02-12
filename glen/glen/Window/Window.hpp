#ifndef GLEN_WINDOW_HPP
#define GLEN_WINDOW_HPP

#include <glen/ogl.h>
#include <glen/Config.hpp>
#include <glen/Graphics/Color.hpp>

#include <glen/Window/WindowStyle.hpp>
#include <glen/Window/VideoMode.hpp>

#include <string>

namespace glen
{

	class Window
	{
	public:

		Window(void);
		~Window(void);

		bool create(VideoMode mode, const std::string &title = "GLEN Window", uint16 style = style::Default);

		void clear(Color c = Color::Black);
		void display();

		void setTitle(const std::string &title);

		inline bool isOpen() const { return glfwGetWindowParam(GLFW_OPENED) == 1; }

	private:

		VideoMode	m_videoMode;

		void _setDefaultGLStates();

	};

}

#endif
