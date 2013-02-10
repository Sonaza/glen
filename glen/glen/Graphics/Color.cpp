#include <glen/Graphics/Color.hpp>

namespace glen
{
// Define the predefined color constants
const Color Color::Black(0, 0, 0);
const Color Color::White(255, 255, 255);
const Color Color::Red(255, 0, 0);
const Color Color::Green(0, 255, 0);
const Color Color::LimeGreen(200, 240, 30);
const Color Color::Blue(0, 0, 255);
const Color Color::Yellow(255, 255, 0);
const Color Color::Orange(255, 210, 0);
const Color Color::Magenta(255, 0, 255);
const Color Color::Cyan(0, 255, 255);
const Color Color::Transparent(0, 0, 0, 0);

///////////////////////////////////////////////////////////
Color::Color() :
	r(0),
	g(0),
	b(0),
	a(0)
{}

///////////////////////////////////////////////////////////
Color::Color(const uint8 r, const uint8 g, const uint8 b, const uint8 a) :
	r(r),
	g(g),
	b(b),
	a(a)
{}

///////////////////////////////////////////////////////////
/*Color::Color(float r, float g, float b, float a) :
	r(static_cast<uint8>(r * 255.f)),
	g(static_cast<uint8>(g * 255.f)),
	b(static_cast<uint8>(b * 255.f)),
	a(static_cast<uint8>(a * 255.f))
{}*/

}
