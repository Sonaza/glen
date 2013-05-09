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
	cam->lookAt(vec3f(0.f, 1.8f, 0.f), vec3f::up);

	//TextureCubemap tcm;
	//tcm.loadFromFile("sky/left.png", "sky/right.png", "sky/top.png", "sky/bottom.png", "sky/front.png", "sky/back.png");

	{
		// Load texture
		AssetManager::loadTexture2D("brick", "test2.png");

		// Create new diffuse material
		Material* mat = AssetManager::createMaterial(Material::Diffuse, "brick");

		// Apply some scaling to the diffuse texture
		mat->getTransform<Texture::Diffuse>()->setScale(5.f, 5.f, 1.f);

		// Load bunny model and apply the material
		AssetManager::loadModel("bunny", "bunny_uvs_normals.obj")
			->setMaterial(mat);

		// Create new entity and attach transform and renderer
		test = new Entity;
		test->attachComponent(new Transform);
		test->attachComponent(new Renderer("bunny"));

		// Send the entity to the world pipeline
		World::addEntity(test);
	}

	{
		// Load texture
		AssetManager::loadTexture2D("uvmap", "uvtest.png");

		// Create new diffuse material
		Material* mat = AssetManager::createMaterial(Material::Diffuse, "uvmap");

		// Load bunny model and apply the material
		AssetManager::loadModel("uvmap", "uvmapped.obj")
			->setMaterial(mat);

		// Create new entity and attach transform and renderer
		uvmapped = new Entity;
		uvmapped->attachComponent(new Transform);
		uvmapped->attachComponent(new Renderer("uvmap"));

		uvmapped->call("setPosition", vec3f(0.f, 250.f, 0.f));
		uvmapped->call("setScale", vec3f(30.f, 30.f, 30.f));
		uvmapped->call("setRotation", vec3f(32.f, 0.f, 19.f));

		// Send the entity to the world pipeline
		World::addEntity(uvmapped);
	}
	
	{
		// Create new diffuse material
		Material* mat = AssetManager::createMaterial(Material::Diffuse, "uvmap");
		
		mat->setOpacity(50);

		// Load bunny model and apply the material
		AssetManager::loadModel("uvmap", "uvmapped.obj")
			->setMaterial(mat);

		// Create new entity and attach transform and renderer
		uvmapped2 = new Entity;
		uvmapped2->attachComponent(new Transform);
		uvmapped2->attachComponent(new Renderer("uvmap"));

		uvmapped2->call("setPosition", vec3f(700.f, 110.f, 800.f));
		uvmapped2->call("setScale", vec3f(100.f, 100.f, 100.f));
		uvmapped2->call("setRotation", vec3f(60.f, 49.f, 40.f));

		// Send the entity to the world pipeline
		World::addEntity(uvmapped2);
	}

	{
		// Load texture
		AssetManager::loadTexture2D("terrain", "grass.png");

		// Create new diffuse material
		Material* mat = AssetManager::createMaterial(Material::Diffuse, "terrain");

		// Apply some scaling to the diffuse texture
		mat->getTransform<Texture2D::Diffuse>()->setScale(220.f, 220.f, 1.f);

		// Load bunny model and apply the material
		AssetManager::loadModel("terrain", "terrainhi.obj")
			->setMaterial(mat);

		// Create new entity and attach transform and renderer
		test2 = new Entity;	
		test2->attachComponent(new Transform);
		test2->attachComponent(new Renderer("terrain"));
		
		test2->call("setPosition", vec3f(0.f, -5.f, -10.f));
		test2->call("setScale", vec3f(40.f, 30.f, 40.f));
		test2->call("setRotation", vec3f(0.f, 0.f, 0.f));

		// Send the entity to the world pipeline
		World::addEntity(test2);
	}


	skybox.push_back(new Skyplane("sky/front.png",	vec3f(0.f, 0.f, 0.f)));
	skybox.push_back(new Skyplane("sky/back.png",	vec3f(0.f, -180.f, 0.f)));

	skybox.push_back(new Skyplane("sky/right.png",	vec3f(0.f, -90.f, 0.f)));
	skybox.push_back(new Skyplane("sky/left.png",	vec3f(0.f, 90.f, 0.f)));

	skybox.push_back(new Skyplane("sky/top.png",	vec3f(-90.f, 0.f, 0.f)));
	skybox.push_back(new Skyplane("sky/bottom.png",	vec3f(90.f, 0.f, 0.f)));

	{
		// Load texture
		AssetManager::loadTexture2D("bgplane", "sphere.png");

		// Create new diffuse material
		Material* mat = AssetManager::createMaterial(Material::Diffuse, "bgplane");

		// Apply some scaling to the diffuse texture
		//mat->getTransform<Texture2D::Diffuse>()->setScale(15.f, 15.f, 1.f);

		// Load bunny model and apply the material
		AssetManager::loadModel("bgplane", "bgplane.obj")
			->setMaterial(mat);
		
		// Create new entity and attach transform and renderer
		bgplane = new Entity;
		bgplane->attachComponent(new Transform);
		bgplane->attachComponent(new Renderer("bgplane"));

		bgplane->call("setPosition", vec3f(0.f, -5.f, -120.f));
		bgplane->call("setScale", vec3f(6.f, 10.f, 6.f));
		bgplane->call("setRotation", vec3f(-90.f, 0.f, 0.f));

		// Send the entity to the world pipeline
		World::addEntity(bgplane);
	}

	ypos = 2.f;
	yvel = 0.f;
	yscale = 1.f;
	yscalevel = 0.f;

	rad = rot = 0.f;

	bounce = false;

	camyvel = 0.f;
	campos.y = 2.f;
	crotzvel = 0.f;
}

//////////////////////////////////////////////////////
void TestScene::unload()
{
	
}

//////////////////////////////////////////////////////
void TestScene::update()
{
	vec2i mp = Input::getMousePos();
	vec2f center = static_cast<vec2f>(Window::getDimensions()) / 2.f;

	vec2f diff;

	//test2->send("setRotation", vec3f(0.f, 360.f * Time.total, 0.f));

	if(!Input::isKeyDown(sf::Keyboard::LControl) && Window::isActive())
	{
		sf::Mouse::setPosition(sf::Vector2i(center.x, center.y), *Window::getWindow());

		diff = vec2f(
			mp.x - center.x,
			mp.y - center.y
		);

		Window::getWindow()->setMouseCursorVisible(false);
	}
	else
	{
		Window::getWindow()->setMouseCursorVisible(true);
	}

	vec3f crot = cam->getRotation();

	crot.y += diff.x / (2.f * center.x) * 330.f;
	crot.x += diff.y / (2.f * center.y) * 250.f;
	crot.x = clamp(crot.x, -89.9f, 89.9f);

	if(Input::isKeyDown(sf::Keyboard::Q))
	{
		crot.z -= 200.f * Time.delta;
	}
	else if(Input::isKeyDown(sf::Keyboard::E))
	{
		crot.z += 200.f * Time.delta;
	}
	else
	{
		crot.z += crotzvel * Time.delta;
		if(fabs(crot.z) > 0.0005f)
			crotzvel += -(crot.z / fabs(crot.z)) * 250.f * Time.delta;

		crotzvel *= 1.f - 0.9f * Time.delta;
	}

	camrot.y += diff.x / (2.f * center.x) * 330.f;
	camrot.x += diff.y / (2.f * center.y) * 250.f;
	camrot.x = clamp(camrot.x, -89.9f, 89.9f);

	cam->setRotation(crot);

	float yrad = camrot.y * 3.141592f / 180.f;

	float multi = (campos.y + 80.f) / 50.f;

	if(Input::isKeyDown(sf::Keyboard::Space))// && campos.y <= 2.1f)
	{
		//camyvel = 40.f;
		campos.y += 50.f * Time.delta * multi;
	}
	else if(Input::isKeyDown(sf::Keyboard::LShift))
	{
		campos.y -= 50.f * Time.delta * multi;
	}

	campos.y = clamp(campos.y, -200.f, 10000.f);

	//camyvel += -40.f * Time.delta;
	//campos.y += camyvel * Time.delta;

	if(campos.y <= 2.f)
	{
		camyvel = 0.f;
		campos.y = 2.f;
	}

	float speed = 8.f * multi;

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

	/*vec3f camdir(
		campos.x + cos(yrad) * (1.f - fabs(camrot.x / 90.f)),
		campos.y - (camrot.x * 3.141592f / 180.f),
		campos.z + sin(yrad) * (1.f - fabs(camrot.x / 90.f))
	);

	cam->setPosition(campos);
	cam->lookAt(camdir, vec3f::up);*/

	cam->setPosition(campos);
	cam->updateLookAt();

	for(std::vector<Skyplane*>::iterator it = skybox.begin(); it != skybox.end(); ++it)
	{
		(*it)->setCamPos(campos);
	}

	if(!bounce)
	{
		yvel += -18.f * Time.delta;
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
		yscalevel += 25.f * Time.delta;// * (yscale > 1.f ? -1.f : 1.f);
		yscale += yscalevel * Time.delta;
		
		if(yscale > 1.f)
		{
			bounce = false;

			yscale = 1.f;
			yscalevel = 0.f;

			yvel = 15.f;
		}
	}

	//float yscale = std::max(0.1f, sin(time * 2.f) * 0.4f + 0.6f);
	//float ypos = std::max(0.01f, cos(time * 2.f + 1.f)) * 0.05f;
	
	rot += 0.3f * 11.f * (ypos / 2.f) * Time.delta;
	rad = rot * 3.141592f / 180.f;

	test->call("setPosition", vec3f(
		cos(-rad) * 20.f * 30.f,
		ypos * 30.f - 90.f,
		sin(-rad) * 20.f * 30.f - 140.f
	));

	test->call("setScale", vec3f(
		50.f * (1.f / yscale) * 50.f,
		50.f * yscale * 50.f,
		50.f * (1.f / yscale) * 50.f
	));

	test->call("setRotation", vec3f(0.f, rot - 85.f, 0.f));
}

//////////////////////////////////////////////////////
void TestScene::render()
{
	
}