#ifndef TESTSCENE_HPP
#define TESTSCENE_HPP

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <glen/glen.hpp>

#include <game/Entities/Spacebox.hpp>
#include <game/Entities/Spacecube.hpp>

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
	
	sf::Clock m_introclock;
	float m_introphase;
	float m_victoryphase;

	enum VictoryState
	{
		Undecided,
		Loss,
		Victory
	} m_victoryState;

	Entity* gametip;
	Entity* victoryplane;
	Entity* failplane;

	Camera* cam;

	sf::Clock m_timer;

	Skybox* skybox;
	std::vector<Spacebox*> boxes;
	std::vector<Spacecube*> spacecubes;

	std::vector<int32> level;

	Entity* grid;
	Entity* cube;
	vec3f cuberot;
	vec3f cubepos, targetpos;
	float cubevely;

	vec3f campos;
	vec3f camrot;

	float velforward;

	float crotzvel;


};

#endif
