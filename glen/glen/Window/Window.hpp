#ifndef WINDOW_H
#define WINDOW_H

#include <glen/ogl.h>
#include <glen/Config.hpp>
#include <glen/Graphics/Color.hpp>

namespace glen
{

class Window
{
public:

	Window(void);
	~Window(void);

	bool create(uint32 width, uint32 height);

	void clear(Color c = Color::Black);
	void display();

	inline bool isOpen() const { return glfwGetWindowParam(GLFW_OPENED) == 1; }

private:

};

}

#endif
