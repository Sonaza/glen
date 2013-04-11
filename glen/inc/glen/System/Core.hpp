#ifndef GLEN_CORE_H
#define GLEN_CORE_H

#include <glen/Graphics/Camera.hpp>
#include <glen/System/Sleep.hpp>

namespace glen
{

	class SceneManager;

	class Core
	{
	public:

		Core(void);
		~Core(void);

		void run();

		void initialize();
		void loop();

		// Managers
		SceneManager*	m_sceneManager;

	private:

		float		m_fpsTimer, m_lastTime, m_outTimer;

		bool		m_running;

	};

}

#endif
