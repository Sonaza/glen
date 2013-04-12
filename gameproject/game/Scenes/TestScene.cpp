#include <game/Scenes/TestScene.hpp>
#include <cmath>

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
	Camera* asd = Camera::create(60.f, 0.01f, 100.f);
	asd->setPosition(0.f, 2.3f, 3.5f);
	asd->lookAt(Vector3f(0.f, 1.8f, 0.f), Vector3f::up);

	AssetManager::loadTexture2D("brick", "test2.png");

	Material* mat = MaterialFactory::diffuse("brick");
	AssetManager::createMaterial("brickmaterial",
		mat);

	mat->getTransform<Texture2D::Diffuse>()->setScale(5.f, 5.f, 1.f);

	AssetManager::loadModel("bunny", "bunny_uvs_normals.obj")
		->setMaterial("brickmaterial");

	test = new Entity;
	test->attachComponent(new Transform);
	test->attachComponent(new Renderer("bunny"));

	//test->send("setPosition", Vector3f(-0.1f, 0.f, 0.f));

	World::addEntity(test);

	/*test2 = new Entity;
	test2->attachComponent(new Transform);
	test2->attachComponent(new Renderer("bunny"));

	test2->send("setPosition", Vector3f(0.1f, 0.f, 0.f));

	World::addEntity(test2);*/

	ypos = 2.f;
	yvel = 0.f;
	yscale = 1.f;
	yscalevel = 0.f;

	bounce = false;
}

//////////////////////////////////////////////////////
void TestScene::unload()
{
	
}

//////////////////////////////////////////////////////
void TestScene::update()
{
	float time = m_timer.getElapsedTime().asSeconds();
	
	if(!bounce)
	{
		yvel += -0.05f;
		ypos += yvel * Time.delta;

		if(ypos <= 0.f)
		{
			yvel = 0.f;
			ypos = 0.f;

			yscalevel = -4.5f;
			bounce = true;
		}
	}

	if(bounce)
	{
		yscalevel += 0.12f;// * (yscale > 1.f ? -1.f : 1.f);
		yscale += yscalevel * Time.delta;
		
		if(yscale > 1.f)
		{
			bounce = false;

			yscale = 1.f;
			yscalevel = 0.f;

			yvel = 6.f;
		}
	}

	//float yscale = std::max(0.1f, sin(time * 2.f) * 0.4f + 0.6f);
	//float ypos = std::max(0.01f, cos(time * 2.f + 1.f)) * 0.05f;

	test->send("setPosition", Vector3f(0.0f, ypos, 0.f));
	test->send("setScale", Vector3f(10.f, 10.f * yscale, 10.f));
	//test->send("setRotation", Vector3f(0.f, 45.f * time, 0.f));
}

//////////////////////////////////////////////////////
void TestScene::render()
{
	
}