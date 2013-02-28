#ifndef GLEN_GLENERROR_HPP
#define GLEN_GLENERROR_HPP

#include <glen/Config.hpp>
#include <glen/Window/MessageBox.hpp>

#include <string>
#include <sstream>

namespace glen
{

	class Error
	{
	public:

		enum Signal
		{
			console = 0,
			info	= 1,
			warning	= 2,
			error	= 3
		};

		template <typename T>
		friend Error& operator<<(Error& left, T right);
		
		friend Error& operator<<(Error& left, Error::Signal right);

	protected:

		std::stringstream out;

	};
	
	template <typename T>
	Error& operator<<(Error& left, T right)
	{
		left.out << right;

		return left;
	}

	extern Error err;

}

#endif
