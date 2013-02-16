#ifndef SCENE_HPP
#define SCENE_HPP

#include <glen/System/Core.hpp>
#include <glen/Window/Window.hpp>

#include <glen/Graphics/Color.hpp>
#include <glen/Graphics/Model.hpp>
#include <glen/Graphics/Texture.hpp>

namespace glen
{

	class Scene
	{
	public:
		Scene(void);
		virtual ~Scene(void);

		inline void init(Core* c) { p_core = c; }

		virtual void load() =0;
		virtual void unload() =0;

		virtual void update() =0;

		virtual void draw() =0;

		inline bool isActive() const { return m_active; }

		inline void activate() { m_active = true; }
		inline void deactivate() { m_active = false; }

	protected:

		Core*	p_core;

	private:

		// Determines if scene is active
		bool	m_active;
		// True when scene assets have been loaded
		bool	m_loaded;

	};

}

#endif
