#include <glen/System/GlenError.hpp>
#include <iostream>

namespace glen
{

	Error err;
	
	////////////////////////////////////////////////////////////////
	Error& operator<<(Error& left, Error::Signal right)
	{
		switch(right)
		{
		case Error::console:
			std::cout << left.out.str() << std::endl;
			break;

		case Error::info:
			msgInfo("Info", left.out.str());
			break;

		case Error::warning:
			msgWarn("Warning", left.out.str());
			break;

		case Error::error:
			msgError("Error", left.out.str());
			break;
		}

		left.out.str("");

		return left;
	}

}