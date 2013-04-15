#ifndef GLEN_INPUTMANAGER_HPP
#define GLEN_INPUTMANAGER_HPP

#include <glen/opengl.hpp>
#include <glen/System/Vector2.hpp>
#include <map>

namespace glen
{

	typedef std::map<const sf::Keyboard::Key, int> KeyHits;
	typedef std::map<const sf::Mouse::Button, int> MouseHits;
	
	namespace Input
	{

		bool isKeyDown(const sf::Keyboard::Key code);
		bool isKeyHit(const sf::Keyboard::Key code);

		bool isMouseDown(const sf::Mouse::Button button);
		bool isMouseHit(const sf::Mouse::Button button);

		Vector2i getMousePos();

		void updateInputs(sf::Event& event);

	}
	
}

#endif GLEN_INPUTMANAGER_HPP
