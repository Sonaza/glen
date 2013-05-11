#ifndef GLEN_UTILITY_HPP
#define GLEN_UTILITY_HPP

#include <glen/System/Types.hpp>
#include <cmath>
#include <algorithm>

namespace glen
{

	namespace Util
	{

		extern const float PI;
		extern const float TWOPI;

		template <class T>
		T clamp(T val, T min, T max)
		{
			return std::max(min, std::min(max, val));
		}

		extern float toradians(float deg);
		extern float todegrees(float rad);

		extern vec3f toradians(vec3f deg);
		extern vec3f todegrees(vec3f rad);

		extern float wrapangle(float a);

		extern float distance(vec2f a, vec2f b);
		extern float distance(vec3f a, vec3f b);

		extern int random_int(int start, int end);
		extern float random_float(float start, float end);

	}
	
}

#endif GLEN_UTILITY_HPP
