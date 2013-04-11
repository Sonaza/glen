#include <glen/Window/VideoMode.hpp>
#include <Windows.h>

namespace glen
{

/////////////////////////////////////////////////////////////////
VideoMode::VideoMode() :
	width(0),
	height(0)
{
}

/////////////////////////////////////////////////////////////////
VideoMode::VideoMode(uint32 width, uint32 height) :
	width(width),
	height(height)
{
}

/////////////////////////////////////////////////////////////////
VideoMode VideoMode::getDesktopMode()
{
	DEVMODE win32Mode;
	win32Mode.dmSize = sizeof(win32Mode);
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &win32Mode);

	return VideoMode(win32Mode.dmPelsWidth, win32Mode.dmPelsHeight); //, win32Mode.dmBitsPerPel
}

}