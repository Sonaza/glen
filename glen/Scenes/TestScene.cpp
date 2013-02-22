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
		test.loadFromFile("ball2.obj");
	}
	catch(std::runtime_error& e) { std::cout << e.what(); }

	tex.loadFromFile("sphere.png");
	test.setTexture(tex);

	test.setPosition(0.f, 0.f, 0.f);
}

//////////////////////////////////////////////////////
void TestScene::unload()
{

}

//////////////////////////////////////////////////////
void TestScene::update()
{
	time = GetTickCount() / 1000.f;

	test.m_program->use();
	test.m_program->setUniform("time", time);

	//test.setScale(1.f, cos(time*2.f)*0.5f+1.f, sin(time*2.f)*0.5f+1.f)
	//float s = 1.2f;//(cos(time / 10.f) * 0.5f + 1.f) * 0.2f;
	//test.setScale(s*0.1f, s*1.5f, s*1.5f);
	//test.setRotation(0.f, time * 25.f, 45.f);
	test.setRotation(0.f, 0.f, 25.f);

	//cam = Camera::activeCamera();
	//cam->setPosition(1.5f, 1.7f+cos(time*2.f)*0.5f, 1.5f+sin(time*2.f)*0.5f);
	//cam->lookAt(Vector3f::zero, Vector3f::up);
}

//////////////////////////////////////////////////////
void TestScene::draw()
{
	test.render();
}