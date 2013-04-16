#ifndef TESTSCENE_HPP
#define TESTSCENE_HPP

#include <glen/glen.hpp>
#include <algorithm>

#define clamp(__val, __min, __max) (std::max((__min), std::min((__max), (__val))))

using namespace glen;

class TestScene : public Scene
{
public:
	TestScene(void);
	~TestScene(void);

	void load();
	void unload();

	void update();

	void render();

private:

	Camera* cam;

	/*Model object;
	Texture2D tex, decal;
	Material* basic;*/

	sf::Clock m_timer;

	Entity* test;
	Entity* test2;
	Entity* bgplane;
	
	Vector3f campos;
	Vector3f camrot;

	float yvel;
	float ypos;

	float yscale;
	float yscalevel;

	float rot, rad;

	bool bounce;

};

#endif
