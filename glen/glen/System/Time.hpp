#ifndef GLEN_TIME_HPP
#define GLEN_TIME_HPP

#include <glen/Config.hpp>

namespace glen
{

	class Time
	{
	public:
		Time(const int64 microseconds);

		float asSeconds() const;
		int64 asMilliseconds() const;
		int64 asMicroseconds() const;

	private:

		// Time in microseconds
		int64 m_ticks;

	};

	extern Time seconds(float amount);
	extern Time milliseconds(int64 amount);
	extern Time microseconds(int64 amount);

}

#endif