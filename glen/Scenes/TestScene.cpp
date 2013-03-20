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
	Camera* asd = Camera::create(45.f, 0.01f, 100.f);
	asd->setPosition(0.f, 0.2f, 0.3f);
	asd->lookAt(Vector3f(0.f, 0.1f, 0.f), Vector3f::up);

	object.loadFromFile("bunny_uvs_normals.obj");

	tex.loadFromFile("test2.png");
	decal.loadFromFile("crome.png");

	basic = MaterialFactory::diffuse(tex);
	basic->setTexture<Texture2D::Specular>(decal);

	object.setMaterial(basic);
	//object.setScale(0.1f, 0.1f, 0.1f);
	//object.setPivot(-0.1f, -0.1f, -0.1f);
	//object.setScale(40.f, 20.0f, 40.f);
	//object.setPosition(0.f, -3.f, -1.f);
}

//////////////////////////////////////////////////////
void TestScene::unload()
{
	//MaterialFactory::unload(basic);
}

//////////////////////////////////////////////////////
void TestScene::update()
{
	time = GetTickCount() / 1000.f;

	//basic->getTransform<Texture2D::Diffuse>()->setPivot(0.5f, 0.5f, 0.f);
	basic->getTransform<Texture2D::Diffuse>()->setScale(25.f, 25.f, 1.f);
	//basic->getTransform<Texture2D::Diffuse>()->setRotation(0.f, 0.f, -90.f);

	basic->getTransform<Texture2D::Specular>()->setScale(16.f, 50.f, 0.f);
	basic->getTransform<Texture2D::Specular>()->setPosition(0.2f * time, 0.04f * time, 0.f);
	//basic->getTransform<Texture2D::Specular>()->setRotation(0.f, 0.f, -90.f);

	//test.m_program->use();
	//test.m_program->setUniform("time", time);

	//test.setScale(1.f, cos(time*2.f)*0.5f+1.f, sin(time*2.f)*0.5f+1.f)
	//float s = 1.2f;//(cos(time / 10.f) * 0.5f + 1.f) * 0.2f;
	//test.setScale(s*0.1f, s*1.5f, s*1.5f);
	object.setRotation(0.f, 45.f * time, 0.f);
	//test.setRotation(0.f, 0.f, 25.f);

	//cam = Camera::activeCamera();
	//cam->setPosition(1.5f, 1.7f+cos(time*2.f)*0.5f, 1.5f+sin(time*2.f)*0.5f);
	//cam->lookAt(Vector3f::zero, Vector3f::up);
}

//////////////////////////////////////////////////////
void TestScene::draw()
{
	object.setPosition(0.06f, cos(time * 5.f) * 0.1f, 0.f);
	object.render();

	object.setPosition(-0.06f, 0.f, 0.f);
	object.render();
}