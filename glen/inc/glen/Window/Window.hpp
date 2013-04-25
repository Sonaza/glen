#ifndef GLEN_WINDOW_HPP
#define GLEN_WINDOW_HPP

#include <glen/System/Types.hpp>

#include <glen/Window/WindowStyle.hpp>
#include <glen/Window/VideoMode.hpp>
#include <glen/Graphics/Color.hpp>

#include <string>

namespace sf
{
	class Window;
}

namespace glen
{

	namespace Window
	{

		void uninit();

		bool create(VideoMode mode, const std::string &title = "GLEN Window", uint32 style = Style::Default);

		void clear(Color c = Color::Black);
		void display();

		void setTitle(const std::string &title);

		void setPosition(vec2i& pos);
		void setPosition(const int32 x, const int32 y);

		bool isOpen();
		bool isActive();

		vec2u getDimensions();
		float getAspectRatio();

		sf::Window* getWindow();

		vec2i getOptimalResolution(const bool fullscreen = false);

		bool checkShaderSupport();

	}

}

#endif
