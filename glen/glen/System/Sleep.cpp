#include <glen/System/Sleep.hpp>
#include <glen/ogl.h>
#include <Windows.h>

namespace glen
{

	void sleep(Time time)
	{
		::Sleep(static_cast<DWORD>(time.asMilliseconds()));
	}

}