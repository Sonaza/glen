#ifndef STARTUP_HPP
#define STARTUP_HPP

#include <memory>
#include <cassert>

namespace glen
{
	class Core;
	class Scene;

	extern void run(Scene* scene);
	extern std::unique_ptr<Core> g_core;
}

#endif
