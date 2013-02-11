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
Core::Core(void) :
	m_window(NULL)
{
}

////////////////////////////////////////////////////////////
Core::~Core(void)
{
	if(m_sceneManager) { delete m_sceneManager; m_sceneManager = NULL; }
}

////////////////////////////////////////////////////////////
int Core::start()
{
	m_window = new(std::nothrow) Window();
	assert(m_window != NULL && "Core::start() Window memory allocation failed");

	try
	{
		m_window->create(1280, 720);
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
	while(m_running && m_window->isOpen())
	{
		m_sceneManager->update();

		m_sceneManager->draw();

		sleep(milliseconds(5));
	}
}

}