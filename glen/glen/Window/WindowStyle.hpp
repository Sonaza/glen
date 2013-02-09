#ifndef WINDOWSTYLE_HPP
#define WINDOWSTYLE_HPP

namespace glen
{
	namespace style
	{
		enum
		{
			Normal		= 1 << 1,
			Resize		= 1 << 2,
			Fullscreen	= 1 << 3,

			Default = Normal
		};
	}
}

#endif