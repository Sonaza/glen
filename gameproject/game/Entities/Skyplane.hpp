#ifndef SKYPLANE_HPP
#define SKYPLANE_HPP

#include <glen/glen.hpp>
#include <string>

using namespace glen;

class Skyplane : public Entity
{
public:
	Skyplane(const std::string &texture, Vector3f rot);
	~Skyplane(void);

	void setCamPos(Vector3f p) { send("setPosition", Vector3f(p.x, p.y + 5.f, p.z)); }

};

#endif
