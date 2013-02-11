#include <glen/System/Sleep.hpp>
#include <Windows.h>

namespace glen
{

	void sleep(Time time)
	{
		::Sleep(time.asMilliseconds());
	}

}