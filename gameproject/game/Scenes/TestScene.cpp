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
	cam = new Camera(75.f, 1.f, 400.f);
	World::addEntity(cam);

	AssetManager::setWorkingDirectory("data/");

	{
		AssetManager::loadTextureCubemap("skybox",
			"sky/left.png", "sky/right.png",
			"sky/top.png", "sky/bottom.png",
			"sky/front.png", "sky/back.png");

		skybox = new Skybox("skybox");

		skybox->call("setColor", Color(240, 240, 250));

		World::addEntity(skybox);
	}

#define cc(_x, _y) (_x + _y * 11)

	char a[] = {
		"21111111001"
		"10001000001"
		"11101110101"
		"10000010111"
		"00011110101"
		"10010000101"
		"10010011101"
		"10110010011"
		"11100110110"
		"00100100100"
		"11111100113"
	};

	for(int i=0; i < 121; ++i)
	{
		level.push_back(a[i]-48);
	}

	for(int i=0; i < 121; ++i)
	{
		if(level[i] == 0) continue;
		
		int x = i % 11 - 5;
		int y = (int)floor(i / 11.f) - 5;

		Spacebox* box = new Spacebox(level[i]-1);
		box->m_draworder = 10000;

		box->call("setScale", vec3f(1.f, 1.f, 1.f));
		box->call("setPosition", vec3f(x, 0.f, y));

		World::addEntity(box);

		boxes.push_back(box);
	}


	for(int i=0; i < 120; ++i)
	{
		Spacecube* box = new Spacecube;
		
		World::addEntity(box);

		spacecubes.push_back(box);
	}

	{
		AssetManager::loadTexture2D("grid", "grid.png");
		Material* mat = AssetManager::createMaterial(Material::Diffuse, "grid");

		mat->setOpacity(80);

		ModelAsset* model = AssetManager::createModel("gridplane.obj")->setMaterial(mat);

		grid = new Entity;
		grid->attachComponent(new Transform);
		grid->attachComponent(new Renderer(model));

		grid->m_draworder = 15500;
		grid->call("setPosition", vec3f(-0.5f, -1.f, -0.5f));

		World::addEntity(grid);
	}

	{
		AssetManager::loadTexture2D("cube", "cube.png");
		Material* mat = AssetManager::createMaterial(Material::Diffuse, "cube");

		mat->setColor(70, 150, 250);

		ModelAsset* model = AssetManager::createModel("cube.obj")->setMaterial(mat);

		cube = new Entity;
		cube->attachComponent(new Transform);
		cube->attachComponent(new Renderer(model));

		World::addEntity(cube);

		cubepos.x = -5.f;
		cubepos.y = -5.f;
		cubepos.z = 7.f;

		targetpos = cubepos;
	}

	velforward = 0.f;
	
	crotzvel = 0.f;

	cubevely = 0.f;

	camrot.x = 40.f;
	camrot.y = -60.f;

	campos.x = -5.f;
	campos.y = 6.f;
	campos.z = 8.f;

	//vec2f center = static_cast<vec2f>(Window::getDimensions()) / 2.f;
	//sf::Mouse::setPosition(sf::Vector2i(center.x, center.y), *Window::getWindow());
}

//////////////////////////////////////////////////////
void TestScene::unload()
{
	
}

//////////////////////////////////////////////////////
void TestScene::update()
{
	skybox->call("setRotation", vec3f(-25.f + cos(Time.total / 3.f) * 8.f, 0.f, 0.f));

	/*vec2i mp = Input::getMousePos();
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
	}*/

	grid->call("setPosition", vec3f(-0.5f, -1.f + cos(Time.total / 5.f) * 0.3f , -0.5f));

#define smoothdelta(_current, _target, _div) ((_target - _current) / _div)

	/*vec2f dir = vec2f(targetpos.x - cubepos.x, targetpos.y - cubepos.y);
	float len = dir.length();
	dir.normalize();*/

	cubepos.x += smoothdelta(cubepos.x, targetpos.x, 8.f);
	cubepos.y += smoothdelta(cubepos.y, targetpos.y, 8.f);

	cubepos.z += cubevely * Time.delta;

	cube->call("setPosition", vec3f(cubepos.x, cubepos.z, cubepos.y));

	int x = (int)targetpos.x + 5;
	int y = (int)targetpos.y + 5;

	if(cubepos.z >= 0.f && cubepos.z <= 2.f)
	{
		if(Input::isKeyHit(sf::Keyboard::Left))		targetpos.x -= 1.f;
		if(Input::isKeyHit(sf::Keyboard::Right))	targetpos.x += 1.f;
		if(Input::isKeyHit(sf::Keyboard::Up))		targetpos.y -= 1.f;
		if(Input::isKeyHit(sf::Keyboard::Down))		targetpos.y += 1.f;
	}

	cubevely += -10.f * Time.delta * (cubepos.z < 0.f ? 2.f : 1.f);

	if(x >= 0 && x < 11 && y >= 0 && y < 11 && level[cc(x, y)] != 0)
	{
		if(cubepos.z <= 0.f)
		{
			cubevely *= -0.1f;
			cubepos.z = 0.f;
		}
	}

	if(Input::isKeyHit(sf::Keyboard::Space))
	{
		//cubepos.x = -5.f;
		//cubepos.y = -5.f;
		cubepos.z = 7.f;

		targetpos = vec3f(-5.f, -5.f, 0.f);

		cubevely = 0.f;
	}

	float cx = std::max(1.f, cubepos.x + 6.f);
	float cy = std::max(1.f, cubepos.y + 6.f);

	camrot.x = 40.f - cy * cy / 20.f;
	camrot.y = -75.f + 5.f * cos(Time.total / 7.f);

	campos.x = -3.2f - 0.5f * cos(Time.total / 7.f) + log(cx * cx) / 2.f;
	campos.y = 5.5f + sin(Time.total / 9.f) * 0.25f - log(cy + 4.f) * 0.8f;
	campos.z = 2.f + log(cy * cy * 2.f);
	
	/*camrot.y += diff.x / (2.f * center.x) * 330.f;
	camrot.x += diff.y / (2.f * center.y) * 250.f;
	camrot.x = Util::clamp(camrot.x, -89.9f, 89.9f);

	if(Input::isKeyDown(sf::Keyboard::Q))
	{
		//camrot.z += 200.f * Time.delta;
		crotzvel -= 600.f * Time.delta;
	}
	else if(Input::isKeyDown(sf::Keyboard::E))
	{
		//camrot.z -= 200.f * Time.delta;
		crotzvel += 600.f * Time.delta;
	}
	//else
	{
		camrot.z += crotzvel * Time.delta;
		camrot.y += camrot.z * Time.delta * 2.f;
		Util::wrapangle(camrot.z);

		if(fabs(camrot.z) > 0.0005f)
			crotzvel += -(camrot.z / fabs(camrot.z)) * 250.f * Time.delta;

		crotzvel *= 1.f - 0.9f * Time.delta;
	}*/

	cam->setRotation(camrot);

	float yrad = camrot.y * 3.141592f / 180.f;

	float multi = 1.5f; //(campos.y + 0.f) / 10.f + (Input::isMouseDown(sf::Mouse::Right) ? 5.f : 0.f);

	/*if(Input::isKeyDown(sf::Keyboard::Space))// && campos.y <= 2.1f)
	{
		//camyvel = 40.f;
		campos.y += 15.f * Time.delta * multi;
	}
	else if(Input::isKeyDown(sf::Keyboard::LShift))
	{
		campos.y -= 15.f * Time.delta * multi;
	}

	campos.y = Util::clamp(campos.y, 1.1f, 100.f);
	
	float speed = 11.f * multi;

	vec3f forward = cam->getForward();

	if(Input::isKeyDown(sf::Keyboard::W))
	{
		//velforward += 10.f * Time.delta * speed;
		campos += forward * Time.delta * speed;
		//campos.x += cos(yrad) * Time.delta * 10.f * speed;
		//campos.z += sin(yrad) * Time.delta * 10.f * speed;
	}
	else if(Input::isKeyDown(sf::Keyboard::S))
	{
		//velforward -= 10.f * Time.delta * speed;
		campos -= forward * Time.delta * speed;
		//campos.x -= cos(yrad) * Time.delta * 10.f * speed;
		//campos.z -= sin(yrad) * Time.delta * 10.f * speed;
	}

	//campos += forward * velforward * Time.delta;
	//velforward *= 1.f - 1.5f * Time.delta;

	if(Input::isKeyDown(sf::Keyboard::F))
	{
		velforward *= 0.9f;
		crotzvel *= 0.5f;
	}

	if(Input::isKeyDown(sf::Keyboard::D))
	{
		campos.x += cos(yrad + 1.5707963f) * Time.delta * speed;
		campos.z += sin(yrad + 1.5707963f) * Time.delta * speed;
	}
	else if(Input::isKeyDown(sf::Keyboard::A))
	{
		campos.x -= cos(yrad + 1.5707963f) * Time.delta * speed;
		campos.z -= sin(yrad + 1.5707963f) * Time.delta * speed;
	}*/

	cam->setPosition(campos);
}

//////////////////////////////////////////////////////
void TestScene::render()
{
	
}