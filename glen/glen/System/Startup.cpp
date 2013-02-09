#include <glen/System/Core.hpp>
#include <glen/System/Startup.hpp>

namespace glen
{

	Core* g_core = NULL;

	int run()
	{
		g_core = new(std::nothrow) glen::Core();

		assert(g_core != NULL && "Core memory allocation failed");

		int status = g_core->start();

		delete g_core;
		g_core = NULL;

		return status;
	}

}