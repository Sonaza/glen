#ifndef TESTSCENE_HPP
#define TESTSCENE_HPP

#include <glen/glen.hpp>
#include <algorithm>

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

	float yvel;
	float ypos;

	float yscale;
	float yscalevel;

	bool bounce;

};

#endif
