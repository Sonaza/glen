#include <glen/System/Utility.hpp>

using namespace glen;

const float Util::PI	= 3.141592653589793f;
const float Util::TWOPI		= 6.283185307179586f;

////////////////////////////////////////////////////
float Util::toradians(float deg)
{
	return deg * 0.0174532925199433f;
}

////////////////////////////////////////////////////
float Util::todegrees(float rad)
{
	return rad * 57.29577951308233f;
}

////////////////////////////////////////////////////
vec3f Util::toradians(vec3f deg)
{
	return vec3f(
		toradians(deg.x),
		toradians(deg.y),
		toradians(deg.z)
	);
}

////////////////////////////////////////////////////
vec3f Util::todegrees(vec3f rad)
{
	return vec3f(
		todegrees(rad.x),
		todegrees(rad.y),
		todegrees(rad.z)
	);
}

////////////////////////////////////////////////////
float Util::wrapangle(float a)
{
	while(a > PI) a -= TWOPI;
	while(a < -PI) a += TWOPI;

	return a;
}

////////////////////////////////////////////////////
float Util::distance(vec2f a, vec2f b)
{
	return length(b-a);
}

////////////////////////////////////////////////////
float Util::distance(vec3f a, vec3f b)
{
	return length(b-a);
}