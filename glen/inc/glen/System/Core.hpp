#ifndef GLEN_CORE_H
#define GLEN_CORE_H

#include <glen/opengl.hpp>
#include <iostream>

namespace glen
{

	class Core
	{
	public:

		Core(void);
		~Core(void);

		void run();

		void initialize();
		void uninitialize();

		void loop();

		void events();

		void update();
		void render();

	private:

		bool		m_running;

	};

}

#endif
