#ifndef GLEN_SPACEBOX_HPP
#define GLEN_SPACEBOX_HPP

#include <glen/opengl.hpp>
#include <glen/Game/Entity.hpp>

namespace glen
{

	class Spacebox : public Entity
	{
	public:
		Spacebox(const int c = 0);
		~Spacebox();

		void update();

		//void activate();

	protected:

		int m_type;

	};

}

#endif GLEN_SKYBOX_HPP
