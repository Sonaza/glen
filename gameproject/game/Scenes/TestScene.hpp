#ifndef TESTSCENE_HPP
#define TESTSCENE_HPP

#include <glen/glen.hpp>
#include <iostream>

using namespace glen;

class TestScene : public Scene
{
public:
	TestScene(void);
	~TestScene(void);

	void load();
	void unload();

	void update();

	void draw();

private:

	Camera* cam;

	float time;

	Model object;
	Texture2D tex, decal;
	Material* basic;

};

#endif
