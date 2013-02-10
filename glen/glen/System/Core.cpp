#include <glen/ogl.h>

#include <glen/System/Core.hpp>
#include <glen/Window/Window.hpp>

#include <iostream>
#include <cassert>
#include <stdexcept>

#include <glen/Window/MessageBox.hpp>

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
	catch(std::exception &e)
	{
		msgError("Exception", e.what());
	}

	loop();

	return 0;
}

////////////////////////////////////////////////////////////
void Core::init()
{
	
}

////////////////////////////////////////////////////////////
void Core::loop()
{
	TestScene scene;

	m_running = true;
	while(m_running)
	{
		scene.draw();
	}
}

}