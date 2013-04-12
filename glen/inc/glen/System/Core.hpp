#ifndef GLEN_CORE_H
#define GLEN_CORE_H

#include <glen/opengl.hpp>

#include <glen/Window/Window.hpp>

#include <glen/Game/World.hpp>

#include <glen/System/AssetManager.hpp>
#include <glen/System/SceneManager.hpp>

#include <glen/Graphics/Camera.hpp>
#include <glen/System/Sleep.hpp>

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

		float		m_fpsTimer, m_lastTime, m_outTimer;

		bool		m_running;

	};

}

#endif
