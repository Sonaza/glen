#include <game/Scenes/TestScene.hpp>

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

	AssetManager::loadTexture2D("brick", "test2.png");

	Material* temp = MaterialFactory::diffuse("brick");
	AssetManager::createMaterial("brickmaterial", temp);

	AssetManager::loadModel("bunny", "bunny_uvs_normals.obj")
		->setMaterial("brickmaterial");

	test = new Entity;
	test->attachComponent(new Transform);
	test->attachComponent(new Renderer("bunny"));

	World::addEntity(test);
}

//////////////////////////////////////////////////////
void TestScene::unload()
{
	
}

//////////////////////////////////////////////////////
void TestScene::update()
{
	time = GetTickCount() / 1000.f;

	test->send("setRotation", Vector3f(0.f, 45.f * time, 0.f));
}

//////////////////////////////////////////////////////
void TestScene::render()
{
	
}