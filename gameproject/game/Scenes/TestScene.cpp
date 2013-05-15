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
		cube->m_draworder =  16000;
		
		cube->attachComponent(new Transform);
		cube->call("setPivot", vec3f(0.f, -0.5f, 0.f));
		cube->attachComponent(new Renderer(model));

		World::addEntity(cube);

		cubepos.x = -5.f;
		cubepos.y = -5.f;
		cubepos.z = 25.f;

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

	m_victoryState = Undecided;

	m_introphase = 1.f;

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

#define linearStep (270.f * Time.delta)
#define sign(_val) (_val / fabs(_val))

	/*vec3f lastcuberot = cuberot;

	if(fabs(cuberot.x) > 0.f)
		cuberot.x += -sign(cuberot.x) * linearStep;

	if(fabs(cuberot.z) > 0.f)
		cuberot.z += -sign(cuberot.z) * linearStep;

	if(sign(lastcuberot.x) != sign(cuberot.x)) cuberot.x = 0.f;
	if(sign(lastcuberot.z) != sign(cuberot.z)) cuberot.z = 0.f;*/

	cuberot.x = cubepos.y * 90.f * ((int)cubepos.y % 2 == 0 ? 1 : -1);
	cuberot.z = cubepos.x * 90.f * ((int)cubepos.x % 2 == 0 ? 1 : -1);

	if(m_introclock.getElapsedTime().asSeconds() > 1.f)
	{
		m_introphase += smoothdelta(m_introphase, 0.f, 40.f);

		float xdelta = smoothdelta(cubepos.x, targetpos.x, 8.f);
		cubepos.x += xdelta;

		float ydelta = smoothdelta(cubepos.y, targetpos.y, 8.f);
		cubepos.y += ydelta;

		cubepos.z += cubevely * Time.delta;
	}

	cube->call("setRotation", cuberot);

	////////////////

	float platformy = 0.f;
	for(std::vector<Spacebox*>::iterator it = boxes.begin(); it != boxes.end(); ++it)
	{
		vec3f pos = (*it)->request<vec3f>("getPosition");

		float x = fabs(pos.x - 0.f) / -10.f;
		float y = fabs(pos.z - 0.f) / -10.f;

		float introy = m_introphase * x * y * 10.f;
		pos.y = cos(pos.x * pos.z / 10.f + Time.total) * (0.05f + m_introphase / 8.f) + introy;

		(*it)->call("setColor", Color(255, 255, 255, (uint8)((1.f - m_introphase) * 255.f)));
		(*it)->call("setPosition", pos);

		if(platformy < 0.f && fabs(pos.x - cubepos.x) <= 0.05f && fabs(pos.z - cubepos.y) <= 0.05f)
		{
			platformy = pos.y;
		}
	}

	cube->call("setPosition", vec3f(cubepos.x, cubepos.z + platformy + 0.5f, cubepos.y));

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

	if(m_victoryState == Undecided)
	{
		if(fabs(cubepos.x - 5.f) <= 0.05f && fabs(cubepos.y - 5.f) <= 0.05f)
		{
			MessageBox(NULL, "YOU IS WIN", "WIN", MB_OK);
			m_victoryState = Victory;
		}

		if(cubepos.z <= -15.f)
		{
			MessageBox(NULL, "YOU IS FAIL\n\nPress Space to retry", "FAIL", MB_OK);
			m_victoryState = Loss;
		}
	}

	if(Input::isKeyHit(sf::Keyboard::Space))
	{
		m_victoryState = Undecided;

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

	campos.x = -3.2f - 0.5f * cos(Time.total / 7.f) + log(cx * cx + m_introphase * 55.f) / 2.f;
	campos.y = 5.5f + sin(Time.total / 9.f) * 0.25f - log(cy + 4.f) * 0.8f + log(1.f + m_introphase * 50.f) * 0.5f;
	campos.z = 2.f + log(cy * cy * 2.f + m_introphase * 505.f);

	cam->setRotation(camrot);
	cam->setPosition(campos);
}

//////////////////////////////////////////////////////
void TestScene::render()
{
	
}