#ifndef GLEN_WINDOW_HPP
#define GLEN_WINDOW_HPP

#include <glen/Config.hpp>

#include <glen/Window/WindowStyle.hpp>
#include <glen/Window/VideoMode.hpp>
#include <glen/Graphics/Color.hpp>
#include <glen/System/Vector2.hpp>

#include <string>

namespace sf
{
	class Window;
}

#define haxtern //extern

namespace glen
{

	namespace Window
	{

		haxtern void uninit();

		haxtern bool create(VideoMode mode, const std::string &title = "GLEN Window", uint32 style = Style::Default);

		haxtern void clear(Color c = Color::Black);
		haxtern void display();

		haxtern void setTitle(const std::string &title);

		haxtern void setPosition(Vector2i& pos);
		haxtern void setPosition(const int32 x, const int32 y);

		haxtern bool isOpen();
		haxtern bool isActive();

		haxtern Vector2u getDimensions();
		haxtern float getAspectRatio();

		haxtern sf::Window* getWindow();

		haxtern Vector2i getOptimalResolution(const bool fullscreen = false);

		haxtern bool checkShaderSupport();

	}

}

#endif
