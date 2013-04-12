#ifndef WINDOWSTYLE_HPP
#define WINDOWSTYLE_HPP

#include <SFML/Window/WindowStyle.hpp>

namespace glen
{

	namespace Style
	{
		enum
		{
			None       = 0,      ///< No border / title bar (this flag and all others are mutually exclusive)
			Titlebar   = 1 << 0, ///< Title bar + fixed border
			Resize     = 1 << 1, ///< Titlebar + resizable border + maximize button
			Close      = 1 << 2, ///< Titlebar + close button
			Fullscreen = 1 << 3, ///< Fullscreen mode (this flag and all others are mutually exclusive)

			Default = Titlebar | Resize | Close ///< Default window style
		};
	}

}

#endif