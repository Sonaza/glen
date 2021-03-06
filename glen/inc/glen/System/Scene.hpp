#ifndef SCENE_HPP
#define SCENE_HPP

#include <glen/System/Core.hpp>
#include <glen/Window/Window.hpp>

#include <glen/opengl.hpp>

namespace glen
{

	class Scene
	{
		friend class SceneManager;

	public:
		Scene(void);
		virtual ~Scene(void);

		virtual void load() =0;
		virtual void unload() =0;

		virtual void update() =0;

		virtual void render() =0;

	protected:

		void updateClocks();

		struct Clocks
		{
			Clocks() : total(0.f), delta(0.f) {}

			float total;
			float delta;
		} Time;

		struct ScreenInfo
		{
			ScreenInfo() : width(0), height(0) {}

			sf::Uint32 width;
			sf::Uint32 height;
		} Screen;

	private:

		sf::Clock	m_totalTimeClock;
		sf::Clock	m_deltaTimeClock;

	};

}

#endif
