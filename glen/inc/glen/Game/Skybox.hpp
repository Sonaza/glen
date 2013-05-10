#ifndef GLEN_SKYBOX_HPP
#define GLEN_SKYBOX_HPP

#include <glen/opengl.hpp>
#include <glen/Game/Entity.hpp>

namespace glen
{
	
	class Skybox : public Entity
	{
	public:
		Skybox();
		~Skybox();

		void loadSkybox(const std::string &cubemap);

		void update();
	};
	
}

#endif GLEN_SKYBOX_HPP
