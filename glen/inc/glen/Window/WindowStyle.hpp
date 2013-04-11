#ifndef WINDOWSTYLE_HPP
#define WINDOWSTYLE_HPP

namespace glen
{

	namespace Style
	{
		enum
		{
			Normal		= 0,	// Unresizable windowed
			Resize		= 1,	// Resizable windowed
			Fullscreen	= 2,	// Fullscreen

			Default		= Normal
		};
	}

}

#endif