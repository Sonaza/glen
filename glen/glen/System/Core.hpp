#ifndef CORE_H
#define CORE_H

#include <string>

namespace glen
{

class Window;

class Core
{
public:

	Core(void);
	~Core(void);

	int start();

	void init();
	void loop();

private:

	Window*		m_window;

};

}

#endif
