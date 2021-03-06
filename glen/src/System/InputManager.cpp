#include <glen/System/InputManager.hpp>
#include <glen/Window/Window.hpp>

using namespace glen;

namespace
{

	KeyHits		m_keyhits;
	MouseHits	m_mousehits;

	////////////////////////////////////////////////////
	KeyHits::iterator _getKeyHit(const sf::Keyboard::Key code)
	{
		return m_keyhits.find(code);
	}

	////////////////////////////////////////////////////
	MouseHits::iterator _getMouseHit(const sf::Mouse::Button button)
	{
		return m_mousehits.find(button);
	}

}

////////////////////////////////////////////////////
bool Input::isKeyDown(const sf::Keyboard::Key code)
{
	return sf::Keyboard::isKeyPressed(code) && Window::isActive();
}

////////////////////////////////////////////////////
bool Input::isKeyHit(const sf::Keyboard::Key code)
{
	KeyHits::iterator it = _getKeyHit(code);
	if(it != m_keyhits.end() && it->second == 0)
	{
		m_keyhits[code]++;
		return true;
	}
	
	return false;
}

////////////////////////////////////////////////////
bool Input::isMouseDown(const sf::Mouse::Button button)
{
	return sf::Mouse::isButtonPressed(button);
}

////////////////////////////////////////////////////
bool Input::isMouseHit(const sf::Mouse::Button button)
{
	MouseHits::iterator it = _getMouseHit(button);
	if(it != m_mousehits.end() && it->second == 0)
	{
		m_mousehits[button]++;
		return true;
	}
	
	return false;
}

////////////////////////////////////////////////////
void Input::updateInputs(sf::Event& event)
{
	switch(event.type)
	{
		//////////////////////////////
		// Keyboard
		{
		case sf::Event::KeyPressed:
			if(_getKeyHit(event.key.code) == m_keyhits.end())
			{
				m_keyhits.insert(std::make_pair(event.key.code, 0));
			}
		break;
		case sf::Event::KeyReleased:
			KeyHits::iterator it = _getKeyHit(event.key.code);
			if(it != m_keyhits.end())
			{
				m_keyhits.erase(it);
			}
		break;
		}

		//////////////////////////////
		// Mouse
		{
		case sf::Event::MouseButtonPressed:
			if(_getMouseHit(event.mouseButton.button) == m_mousehits.end())
			{
				m_mousehits.insert(std::make_pair(event.mouseButton.button, 0));
			}
		break;
		case sf::Event::MouseButtonReleased:
			MouseHits::iterator it = _getMouseHit(event.mouseButton.button);
			if(it != m_mousehits.end())
			{
				m_mousehits.erase(it);
			}
		break;
		}
	}
}

////////////////////////////////////////////////////
vec2i Input::getMousePos()
{
	sf::Vector2i temp = sf::Mouse::getPosition(*Window::getWindow());
	return vec2i(temp.x, temp.y);
}
