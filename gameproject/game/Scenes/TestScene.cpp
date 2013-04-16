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
	cam = Camera::create(75.f, 0.01f, 400.f);
	cam->setPosition(0.f, 4.3f, 6.f);
	cam->lookAt(Vector3f(0.f, 1.8f, 0.f), Vector3f::up);

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
		mat->getTransform<Texture2D::Diffuse>()->setScale(25.f, 25.f, 1.f);

		// Load bunny model and apply the material
		AssetManager::loadModel("terrain", "terrain.obj")
			->setMaterial("terrainmaterial");

		// Create new entity and attach transform and renderer
		test2 = new Entity;
		test2->attachComponent(new Transform);
		test2->attachComponent(new Renderer("terrain"));
		
		test2->send("setPosition", Vector3f(0.f, 0.f, 0.f));
		test2->send("setScale", Vector3f(2.f, 1.f, 2.f));
		test2->send("setRotation", Vector3f(0.f, 210.f, 0.f));

		// Send the entity to the world pipeline
		World::addEntity(test2);
	}

	{
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

		bgplane->send("setPosition", Vector3f(0.f, 7.f, -29.f));
		bgplane->send("setScale", Vector3f(6.f, 6.f, 6.f));
		bgplane->send("setRotation", Vector3f(-15.f, 0.f, 0.f));

		// Send the entity to the world pipeline
		World::addEntity(bgplane);
	}

	ypos = 2.f;
	yvel = 0.f;
	yscale = 1.f;
	yscalevel = 0.f;

	rad = rot = 0.f;

	bounce = false;

	campos.y = 2.f;
}

//////////////////////////////////////////////////////
void TestScene::unload()
{
	
}

//////////////////////////////////////////////////////
void TestScene::update()
{
	Vector2i mp = Input::getMousePos();
	Vector2f center = static_cast<Vector2f>(Window::getDimensions()) / 2.f;

	Vector2f diff;

	if(!Input::isKeyDown(sf::Keyboard::LControl))
	{
		sf::Mouse::setPosition(sf::Vector2i(center.x, center.y), *Window::getWindow());

		diff = Vector2f(
			mp.x - center.x,
			mp.y - center.y
		);
	}

	camrot.y += diff.x / (2.f * center.x) * 339.f;

	camrot.x += diff.y / (2.f * center.y) * 279.f;
	camrot.x = clamp(camrot.x, -90.f, 90.f);

	float yrad = camrot.y * 3.141592f / 180.f;

	if(Input::isKeyDown(sf::Keyboard::W))
	{
		campos.x += cos(yrad) * Time.delta * 10.f;
		campos.z += sin(yrad) * Time.delta * 10.f;
	}
	else if(Input::isKeyDown(sf::Keyboard::S))
	{
		campos.x -= cos(yrad) * Time.delta * 10.f;
		campos.z -= sin(yrad) * Time.delta * 10.f;
	}

	if(Input::isKeyDown(sf::Keyboard::D))
	{
		campos.x += cos(yrad + 1.5707963f) * Time.delta * 10.f;
		campos.z += sin(yrad + 1.5707963f) * Time.delta * 10.f;
	}
	else if(Input::isKeyDown(sf::Keyboard::A))
	{
		campos.x -= cos(yrad + 1.5707963f) * Time.delta * 10.f;
		campos.z -= sin(yrad + 1.5707963f) * Time.delta * 10.f;
	}

	//cam->setRotation(camrot.x, camrot.y, 0.f);

	Vector3f camdir(
		campos.x + cos(yrad),
		campos.y - (camrot.x * 3.141592f / 180.f),
		campos.z + sin(yrad)
	);

	cam->setPosition(campos);
	cam->lookAt(camdir, Vector3f::up);

	/*float xmul = mp.x / static_cast<float>(Window::getDimensions().x);
	xmul = std::max(0.f, std::min(1.f, xmul)) / 2.f + 1.25f;

	float ymul = 1.f - mp.y / static_cast<float>(Window::getDimensions().y);
	ymul = std::max(0.f, std::min(1.f, ymul));*/
	
	//cam->setPosition(0.f + cos(xmul) * 5.5f, 3.5f + (1.f - ymul) * 2.f, sin(xmul) * 5.5f);
	//cam->lookAt(Vector3f(0.f, 1.f + ymul * 2.5f, xmul), Vector3f::up);

	if(!bounce)
	{
		yvel += -20.f * Time.delta;
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
		yscalevel += 20.f * Time.delta;// * (yscale > 1.f ? -1.f : 1.f);
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
	
	rot += 360.f * (ypos / 2.f) * Time.delta;
	rad = rot * 3.141592f / 180.f;

	test->send("setPosition", Vector3f(cos(-rad) * 2.5f, ypos, sin(-rad) * 2.5f));
	test->send("setScale", Vector3f(
		10.f * (1.f / yscale),
		10.f * yscale,
		10.f * (1.f / yscale)
	));

	test->send("setRotation", Vector3f(0.f, rot - 85.f, 0.f));
}

//////////////////////////////////////////////////////
void TestScene::render()
{
	
}