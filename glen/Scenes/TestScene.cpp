#include <Scenes/TestScene.hpp>
#include <cmath>
#include <Windows.h>

//////////////////////////////////////////////////////
TestScene::TestScene(void)
{
}

//////////////////////////////////////////////////////
TestScene::~TestScene(void)
{
}

//////////////////////////////////////////////////////
void TestScene::load()
{
	try
	{
		test.loadFromFile("cube.obj");
	}
	catch(std::runtime_error& e) { std::cout << e.what(); }

	tex.loadFromFile("test.png");
	test.setTexture(tex);

	test.setPosition(0.f, 0.f, 0.f);
	test.setScale(1.f, 0.75f, 1.f);
}

//////////////////////////////////////////////////////
void TestScene::unload()
{

}

//////////////////////////////////////////////////////
void TestScene::update()
{
	time = GetTickCount() / 1000.f;

	test.setScale(1.f, cos(time*2.f)*0.5f+1.f, sin(time*2.f)*0.5f+1.f);
	test.setRotation(0.f, time * 45.f, 0.f);
}

//////////////////////////////////////////////////////
void TestScene::draw()
{
	test.render();
}