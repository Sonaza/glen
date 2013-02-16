#ifndef TESTSCENE_HPP
#define TESTSCENE_HPP

#include <glen/Graphics/Scene.hpp>
#include <iostream>

class TestScene : public glen::Scene
{
public:
	TestScene(void);
	~TestScene(void);

	void load();
	void unload();

	void update();

	void draw();

private:

	float time;

	glen::Model test;
	glen::Texture tex;

};

#endif
