#ifndef SKYPLANE_HPP
#define SKYPLANE_HPP

#include <glen/glen.hpp>
#include <string>

using namespace glen;

class Skyplane : public Entity
{
public:
	Skyplane(const std::string &texture, vec3f rot);
	~Skyplane(void);

	void setCamPos(vec3f p) { send("setPosition", vec3f(p.x, p.y + 5.f, p.z)); }

};

#endif
