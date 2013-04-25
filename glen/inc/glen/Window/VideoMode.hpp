#ifndef GLEN_VIDEOMODE_HPP
#define GLEN_VIDEOMODE_HPP

#include <glen/System/Types.hpp>

namespace glen
{

	class VideoMode
	{
	public:

		VideoMode();
		VideoMode(uint32 width, uint32 height);

		static VideoMode getDesktopMode();

		uint32 width;
		uint32 height;
		//uint32 bitsPerPixel;

	};

}

#endif
