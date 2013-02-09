#ifndef MESSAGEBOX_HPP
#define MESSAGEBOX_HPP

#include <Windows.h>
#include <string>

namespace glen
{

	extern void msgInfo(const std::string &title, const std::string &msg);
	extern void msgWarn(const std::string &title, const std::string &msg);
	extern void msgError(const std::string &title, const std::string &msg);

}

#endif
