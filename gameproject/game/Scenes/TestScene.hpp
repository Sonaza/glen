#ifndef TESTSCENE_HPP
#define TESTSCENE_HPP

#include <glen/glen.hpp>

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

	sf::Clock m_timer;

	Skybox* skybox;

	Entity* test;
	Entity* test2;
	Entity* bgplane;
	Entity* uvmapped;
	Entity* uvmapped2;

	float camyvel;
	vec3f campos;
	vec3f camrot;

	float crotzvel;

	float yvel;
	float ypos;

	float yscale;
	float yscalevel;

	float rot, rad;

	bool bounce;

};

#endif
