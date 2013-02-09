#include <glen/Window/MessageBox.hpp>

namespace glen
{

	void msgInfo(const std::string &title, const std::string &msg)
	{
		MessageBoxA(NULL, msg.c_str(), title.c_str(), MB_ICONINFORMATION | MB_OK);
	}

	void msgWarn(const std::string &title, const std::string &msg)
	{
		MessageBoxA(NULL, msg.c_str(), title.c_str(), MB_ICONEXCLAMATION | MB_OK);
	}

	void msgError(const std::string &title, const std::string &msg)
	{
		MessageBoxA(NULL, msg.c_str(), title.c_str(), MB_ICONERROR | MB_OK);
	}

}