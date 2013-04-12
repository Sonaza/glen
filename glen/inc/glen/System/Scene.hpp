#ifndef SCENE_HPP
#define SCENE_HPP

#include <glen/System/Core.hpp>
#include <glen/Window/Window.hpp>

#include <glen/Graphics/Camera.hpp>

#include <glen/Graphics/Color.hpp>
#include <glen/Graphics/Model.hpp>
#include <glen/Graphics/Texture2D.hpp>

#include <glen/Graphics/Material.hpp>
#include <glen/Graphics/MaterialFactory.hpp>
#include <glen/Graphics/TextureTransform.hpp>

namespace glen
{

	class Scene
	{
	public:
		Scene(void);
		virtual ~Scene(void);

		virtual void load() =0;
		virtual void unload() =0;

		virtual void update() =0;

		virtual void render() =0;

	private:

		// True when scene assets have been loaded
		bool	m_loaded;

	};

}

#endif
