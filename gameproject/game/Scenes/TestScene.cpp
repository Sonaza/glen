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
	cam = Camera::create(80.f, 1.f, 50000.f);
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
		mat->getTransform<Texture2D::Diffuse>()->setScale(90.f, 90.f, 1.f);

		// Load bunny model and apply the material
		AssetManager::loadModel("terrain", "terrainhi.obj")
			->setMaterial("terrainmaterial");

		// Create new entity and attach transform and renderer
		test2 = new Entity;	
		test2->attachComponent(new Transform);
		test2->attachComponent(new Renderer("terrain"));
		
		test2->send("setPosition", Vector3f(0.f, -2.f, 0.f));
		test2->send("setScale", Vector3f(14.f, 6.f, 14.f));
		test2->send("setRotation", Vector3f(0.f, 0.f, 0.f));

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

		bgplane->send("setPosition", Vector3f(0.f, 13.f, -29.f));
		bgplane->send("setScale", Vector3f(6.f, 6.f, 6.f));
		bgplane->send("setRotation", Vector3f(-7.f, 0.f, 0.f));

		// Send the entity to the world pipeline
		World::addEntity(bgplane);
	}

	skybox.push_back(new Skyplane("sky/front.png",	Vector3f(0.f, 0.f, 0.f)));
	skybox.push_back(new Skyplane("sky/back.png",	Vector3f(0.f, -180.f, 0.f)));

	skybox.push_back(new Skyplane("sky/right.png",	Vector3f(0.f, -90.f, 0.f)));
	skybox.push_back(new Skyplane("sky/left.png",	Vector3f(0.f, 90.f, 0.f)));

	skybox.push_back(new Skyplane("sky/top.png",	Vector3f(-90.f, 0.f, 0.f)));
	skybox.push_back(new Skyplane("sky/bottom.png",	Vector3f(90.f, 0.f, 0.f)));

	ypos = 2.f;
	yvel = 0.f;
	yscale = 1.f;
	yscalevel = 0.f;

	rad = rot = 0.f;

	bounce = false;

	camyvel = 0.f;
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

	//test2->send("setRotation", Vector3f(0.f, 360.f * Time.total, 0.f));

	if(!Input::isKeyDown(sf::Keyboard::LControl) && Window::isActive())
	{
		sf::Mouse::setPosition(sf::Vector2i(center.x, center.y), *Window::getWindow());

		diff = Vector2f(
			mp.x - center.x,
			mp.y - center.y
		);

		Window::getWindow()->setMouseCursorVisible(false);
	}
	else
	{
		Window::getWindow()->setMouseCursorVisible(true);
	}

	camrot.y += diff.x / (2.f * center.x) * 330.f;
	camrot.x += diff.y / (2.f * center.y) * 250.f;
	camrot.x = clamp(camrot.x, -89.9f, 89.9f);

	float yrad = camrot.y * 3.141592f / 180.f;

	float multi = (campos.y + 40.f) / 50.f;

	if(Input::isKeyDown(sf::Keyboard::Space))// && campos.y <= 2.1f)
	{
		//camyvel = 40.f;
		campos.y += 40.f * Time.delta * multi;
	}
	else if(Input::isKeyDown(sf::Keyboard::LShift))
	{
		campos.y -= 40.f * Time.delta * multi;
	}

	campos.y = clamp(campos.y, 2.f, 2000.f);

	//camyvel += -40.f * Time.delta;
	//campos.y += camyvel * Time.delta;

	if(campos.y <= 2.f)
	{
		camyvel = 0.f;
		campos.y = 2.f;
	}

	float speed = 5.f * multi;

	if(Input::isKeyDown(sf::Keyboard::W))
	{
		campos.x += cos(yrad) * Time.delta * 10.f * speed;
		campos.z += sin(yrad) * Time.delta * 10.f * speed;
	}
	else if(Input::isKeyDown(sf::Keyboard::S))
	{
		campos.x -= cos(yrad) * Time.delta * 10.f * speed;
		campos.z -= sin(yrad) * Time.delta * 10.f * speed;
	}

	if(Input::isKeyDown(sf::Keyboard::D))
	{
		campos.x += cos(yrad + 1.5707963f) * Time.delta * 10.f * speed;
		campos.z += sin(yrad + 1.5707963f) * Time.delta * 10.f * speed;
	}
	else if(Input::isKeyDown(sf::Keyboard::A))
	{
		campos.x -= cos(yrad + 1.5707963f) * Time.delta * 10.f * speed;
		campos.z -= sin(yrad + 1.5707963f) * Time.delta * 10.f * speed;
	}

	//cam->setRotation(camrot.x, camrot.y, 0.f);

	Vector3f camdir(
		campos.x + cos(yrad) * (1.f - fabs(camrot.x / 90.f)),
		campos.y - (camrot.x * 3.141592f / 180.f),
		campos.z + sin(yrad) * (1.f - fabs(camrot.x / 90.f))
	);

	cam->setPosition(campos);
	cam->lookAt(camdir, Vector3f::up);

	for(std::vector<Skyplane*>::iterator it = skybox.begin(); it != skybox.end(); ++it)
	{
		(*it)->setCamPos(campos);
	}


	if(!bounce)
	{
		yvel += -35.f * Time.delta;
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
		yscalevel += 18.f * Time.delta;// * (yscale > 1.f ? -1.f : 1.f);
		yscale += yscalevel * Time.delta;
		
		if(yscale > 1.f)
		{
			bounce = false;

			yscale = 1.f;
			yscalevel = 0.f;

			yvel = 25.f;
		}
	}

	//float yscale = std::max(0.1f, sin(time * 2.f) * 0.4f + 0.6f);
	//float ypos = std::max(0.01f, cos(time * 2.f + 1.f)) * 0.05f;
	
	rot += 11.f * (ypos / 2.f) * Time.delta;
	rad = rot * 3.141592f / 180.f;

	test->send("setPosition", Vector3f(cos(-rad) * 20.f, ypos -1.f, sin(-rad) * 20.f));
	test->send("setScale", Vector3f(
		50.f * (1.f / yscale),
		50.f * yscale,
		50.f * (1.f / yscale)
	));

	test->send("setRotation", Vector3f(0.f, rot - 85.f, 0.f));
}

//////////////////////////////////////////////////////
void TestScene::render()
{
	
}