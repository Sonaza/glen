#ifndef GLEN_SPACECUBE_HPP
#define GLEN_SPACECUBE_HPP

#include <glen/opengl.hpp>
#include <glen/Game/Entity.hpp>
#include <glen/System/Types.hpp>

namespace glen
{

	class Transform;

	class Spacecube : public Entity
	{
	public:
		Spacecube();
		~Spacecube();

		void update();

	private:

		Transform* t;
		sf::Clock deltaclock, totalclock;

		float offset;

		vec3f rotvel;
	};

}

#endif GLEN_SPACECUBE_HPP
