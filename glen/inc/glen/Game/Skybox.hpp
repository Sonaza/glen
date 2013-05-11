#ifndef GLEN_SKYBOX_HPP
#define GLEN_SKYBOX_HPP

#include <glen/opengl.hpp>
#include <glen/Game/Entity.hpp>

namespace glen
{
	
	class Skybox : public Entity
	{
	public:
		Skybox(const std::string &cubemap);
		~Skybox();

		void update();
	};
	
}

#endif GLEN_SKYBOX_HPP
