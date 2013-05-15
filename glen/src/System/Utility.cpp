#include <glen/System/Utility.hpp>
#include <cstdlib>
#include <ctime>

using namespace glen;

namespace
{
	bool _randseeded = false;
}

const float Util::PI	= 3.141592653589793f;
const float Util::TWOPI	= 6.283185307179586f;

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
float Util::wrapradangle(float a)
{
	while(a > PI) a -= TWOPI;
	while(a < -PI) a += TWOPI;

	return a;
}

////////////////////////////////////////////////////
float Util::wrapdegangle(float a)
{
	while(a > 180.f) a -= 360.f;
	while(a < -180.f) a += 360.f;

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

////////////////////////////////////////////
int Util::random_int(int start, int end)
{
	if(!_randseeded)
	{
		srand((unsigned int)std::time(0));
		_randseeded = true;
	}

	int diff = end - start + 1;
	return rand() % diff + start;
}

////////////////////////////////////////////
float Util::random_float(float start, float end)
{
	if(!_randseeded)
	{
		srand((unsigned int)std::time(0));
		_randseeded = true;
	}
	
	float diff = end - start;
	return start + (float)rand() / ((float)RAND_MAX / diff);
}