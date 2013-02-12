#ifndef WINDOWSTYLE_HPP
#define WINDOWSTYLE_HPP

namespace glen
{

	namespace style
	{
		enum
		{
			Normal		= 0,
			Resize		= 1 << 1,
			Fullscreen	= 1 << 2,

			Default		= Normal
		};
	}

}

#endif