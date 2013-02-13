#ifndef CORE_H
#define CORE_H

#include <glen/System/Sleep.hpp>
#include <string>

namespace glen
{

	class SceneManager;

	class Core
	{
	public:

		Core(void);
		~Core(void);

		int start();

		void init();
		void loop();

	private:

		bool		m_running;

		// Managers
		SceneManager*	m_sceneManager;

	};

}

#endif
