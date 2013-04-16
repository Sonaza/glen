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

namespace glen
{

	namespace Window
	{

		extern void uninit();

		extern bool create(VideoMode mode, const std::string &title = "GLEN Window", uint32 style = Style::Default);

		extern void clear(Color c = Color::Black);
		extern void display();

		extern void setTitle(const std::string &title);

		extern void setPosition(Vector2i& pos);
		extern void setPosition(const int32 x, const int32 y);

		extern bool isOpen();
		extern bool isActive();

		extern Vector2u getDimensions();
		extern float getAspectRatio();

		extern sf::Window* getWindow();

	}

}

#endif