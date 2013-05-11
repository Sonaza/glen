#ifndef TESTSCENE_HPP
#define TESTSCENE_HPP

#include <glen/glen.hpp>

#include <game/Entities/Spacebox.hpp>

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
	std::vector<Spacebox*> boxes;

	std::vector<int32> level;

	Entity* cube;
	vec3f cubepos, targetpos;
	float cubevely;

	vec3f campos;
	vec3f camrot;

	float velforward;

	float crotzvel;


};

#endif
