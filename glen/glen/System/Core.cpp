#include <glen/ogl.h>

#include <glen/System/Core.hpp>
#include <glen/Window/Window.hpp>

#include <iostream>
#include <cassert>
#include <stdexcept>

#include <glen/Window/MessageBox.hpp>
#include <glen/System/SceneManager.hpp>

#include <Scenes/TestScene.hpp>

namespace glen
{

////////////////////////////////////////////////////////////
Core::Core(void)
{
}

////////////////////////////////////////////////////////////
Core::~Core(void)
{
	Window::deinit();

	if(m_sceneManager) { delete m_sceneManager; m_sceneManager = NULL; }
}

////////////////////////////////////////////////////////////
int Core::start()
{
	try
	{
		Window::create(VideoMode(1280, 720), "Derp", Style::Resize);
	}
	catch(std::exception &e) { msgError("Exception", e.what()); }

	init();

	loop();

	return 0;
}

////////////////////////////////////////////////////////////
void Core::init()
{
	m_sceneManager = new(std::nothrow) SceneManager(this);

	m_sceneManager->add("test", new(std::nothrow) TestScene, true);
}

////////////////////////////////////////////////////////////
void Core::loop()
{
	m_running = true;
	while(m_running && Window::isOpen())
	{
		Window::clear(Color::LimeGreen);

		m_sceneManager->update();

		m_sceneManager->draw();

		Window::display();

		sleep(milliseconds(5));
	}
}

}