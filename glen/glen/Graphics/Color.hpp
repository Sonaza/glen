#ifndef COLOR_HPP
#define COLOR_HPP

#include <glen/Config.hpp>

namespace glen
{

	class Color
	{
	public:

		Color();
		Color(const uint8 r, const uint8 g, const uint8 b, const uint8 a = 255);

		uint8 r;
		uint8 g;
		uint8 b;
		uint8 a;

		static const Color Black;
		static const Color White;
		static const Color Red;
		static const Color Green;
		static const Color LimeGreen;
		static const Color Blue;
		static const Color Yellow;
		static const Color Orange;
		static const Color Magenta;
		static const Color Cyan;
		static const Color Transparent;

	};

}

#endif