#ifndef TESTSCENE_HPP
#define TESTSCENE_HPP

#include <glen/Graphics/Scene.hpp>
#include <iostream>

#include <glen/Graphics/Materials/DiffuseMaterial.hpp>

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

	Model test;
	Texture tex, decal;
	DiffuseMaterial basic;

};

#endif
