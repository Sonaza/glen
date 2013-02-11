#ifndef CORE_H
#define CORE_H

#include <glen/System/Sleep.hpp>
#include <string>

namespace glen
{

	class Window;

	class SceneManager;

	class Core
	{
	public:

		Core(void);
		~Core(void);

		int start();

		void init();
		void loop();

		Window* getWindow() const { return m_window; }

	private:

		bool		m_running;

		// Program window
		Window*			m_window;

		// Managers
		SceneManager*	m_sceneManager;

	};

}

#endif
