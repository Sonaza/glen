#ifndef GLEN_WORLD_HPP
#define GLEN_WORLD_HPP

#include <vector>
#include <cassert>

//#include <Box2D/Box2D.h>

#include <glen/Game/Message.hpp>

namespace glen
{
	
	class Core;
	class Entity;

	typedef std::vector<Entity*> EntityList;

	namespace World
	{

		void init();
		void uninit();

		void sendGlobal(const std::string &type, boost::any data);
		void sendGlobal(const Message &msg);

		void addEntity(Entity*);
		void clear();

		void update();
		void render();

	}
	
}

#endif GLEN_WORLD_HPP
