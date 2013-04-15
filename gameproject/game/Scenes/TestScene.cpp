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
	Camera* asd = Camera::create(80.f, 0.01f, 100.f);
	asd->setPosition(0.f, 2.3f, 4.f);
	asd->lookAt(Vector3f(0.f, 1.8f, 0.f), Vector3f::up);

	{
		// Load texture
		AssetManager::loadTexture2D("brick", "test2.png");

		// Create new diffuse material
		Material* mat = MaterialFactory::diffuse("brick");
		AssetManager::createMaterial("brickmaterial", mat);

		// Apply some scaling to the diffuse texture
		mat->getTransform<Texture2D::Diffuse>()->setScale(5.f, 5.f, 1.f);

		// Load bunny model and apply the material
		AssetManager::loadModel("bunny", "bunny_uvs_normals.obj")
			->setMaterial("brickmaterial");

		// Create new entity and attach transform and renderer
		test = new Entity;
		test->attachComponent(new Transform);
		test->attachComponent(new Renderer("bunny"));

		// Send the entity to the world pipeline
		World::addEntity(test);
	}

	{
		// Load texture
		AssetManager::loadTexture2D("terrain", "grass.png");

		// Create new diffuse material
		Material* mat = MaterialFactory::diffuse("terrain");
		AssetManager::createMaterial("terrainmaterial", mat);

		// Apply some scaling to the diffuse texture
		mat->getTransform<Texture2D::Diffuse>()->setScale(15.f, 15.f, 1.f);

		// Load bunny model and apply the material
		AssetManager::loadModel("terrain", "terrain.obj")
			->setMaterial("terrainmaterial");

		// Create new entity and attach transform and renderer
		test2 = new Entity;
		test2->attachComponent(new Transform);
		test2->attachComponent(new Renderer("terrain"));
		
		test2->send("setScale", Vector3f(6.f, 1.1f, 6.f));
		test2->send("setRotation", Vector3f(-6.f, 210.f, 0.f));

		// Send the entity to the world pipeline
		World::addEntity(test2);
	}

	/*{
		// Load texture
		AssetManager::loadTexture2D("bgplane", "bg.jpg");

		// Create new diffuse material
		Material* mat = MaterialFactory::diffuse("bgplane");
		AssetManager::createMaterial("bgplane", mat);

		// Apply some scaling to the diffuse texture
		//mat->getTransform<Texture2D::Diffuse>()->setScale(15.f, 15.f, 1.f);

		// Load bunny model and apply the material
		AssetManager::loadModel("bgplane", "bgplane.obj")
			->setMaterial("bgplane");
		
		// Create new entity and attach transform and renderer
		bgplane = new Entity;
		bgplane->attachComponent(new Transform);
		bgplane->attachComponent(new Renderer("bgplane"));

		bgplane->send("setPosition", Vector3f(0.f, 10.f, -29.f));
		bgplane->send("setScale", Vector3f(5.8f, 5.8f, 5.8f));
		bgplane->send("setRotation", Vector3f(-7.f, 0.f, 0.f));

		// Send the entity to the world pipeline
		World::addEntity(bgplane);
	}*/

	ypos = 2.f;
	yvel = 0.f;
	yscale = 1.f;
	yscalevel = 0.f;

	rot = 0.f;

	bounce = false;
}

//////////////////////////////////////////////////////
void TestScene::unload()
{
	
}

//////////////////////////////////////////////////////
void TestScene::update()
{
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
		yscalevel += 0.11f;// * (yscale > 1.f ? -1.f : 1.f);
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
	test->send("setScale", Vector3f(
		10.f * (1.f / yscale),
		10.f * yscale,
		10.f * (1.f / yscale)
	));

	rot += 360.f * (ypos / 2.f) * Time.delta;

	test->send("setRotation", Vector3f(0.f, rot, 0.f));
}

//////////////////////////////////////////////////////
void TestScene::render()
{
	
}