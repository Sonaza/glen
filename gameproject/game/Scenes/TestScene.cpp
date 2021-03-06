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
		"20111001111"
		"10101011001"
		"11101010011"
		"00001110010"
		"14400000110"
		"10444444100"
		"11000000000"
		"01001110000"
		"11001040411"
		"10011044401"
		"11110000003"
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

	{
		AssetManager::loadTexture2D("win", "win.png");
		Material* mat = AssetManager::createMaterial(Material::Diffuse, "win");

		ModelAsset* model = AssetManager::createModel("victoryplane.obj")->setMaterial(mat);

		victoryplane = new Entity;
		victoryplane->m_draworder = 16100;

		victoryplane->attachComponent(new Transform);
		victoryplane->attachComponent(new Renderer(model));

		victoryplane->call("setPosition", vec3f(-0.5f, 9.f, -3.f));
		victoryplane->call("setRotation", vec3f(40.f, 9.f, 0.f));

		World::addEntity(victoryplane);

		victoryplane->setEnabled(false);
	}

	{
		AssetManager::loadTexture2D("lose", "lose.png");
		Material* mat = AssetManager::createMaterial(Material::Diffuse, "lose");

		ModelAsset* model = AssetManager::createModel("victoryplane.obj")->setMaterial(mat);

		failplane = new Entity;
		failplane->m_draworder = 16100;

		failplane->attachComponent(new Transform);
		failplane->attachComponent(new Renderer(model));

		failplane->call("setPosition", vec3f(-0.5f, 9.f, -3.f));
		failplane->call("setRotation", vec3f(40.f, 9.f, 0.f));

		World::addEntity(failplane);

		failplane->setEnabled(false);
	}

	{
		AssetManager::loadTexture2D("gametip", "gametip.png");
		Material* mat = AssetManager::createMaterial(Material::Diffuse, "gametip");

		ModelAsset* model = AssetManager::createModel("victoryplane.obj")->setMaterial(mat);

		gametip = new Entity;
		gametip->m_draworder = 16200;

		gametip->attachComponent(new Transform);
		gametip->attachComponent(new Renderer(model));

		gametip->call("setPosition", vec3f(4.f, 1.f, -7.4f));
		gametip->call("setRotation", vec3f(65.f, -3.f, 14.f));
		gametip->call("setScale",    vec3f(2.f, 1.f, 2.f));

		World::addEntity(gametip);
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

	m_victoryphase = 0.f;
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
	
	grid->call("setPosition", vec3f(-0.5f, -1.f + cos(Time.total / 5.f) * 0.3f , -0.5f));

#define smoothdelta(_current, _target, _div) (((_target) - (_current)) / (_div))

	/*vec2f dir = vec2f(targetpos.x - cubepos.x, targetpos.y - cubepos.y);
	float len = dir.length();
	dir.normalize();*/

#define linearStep (270.f * Time.delta)
#define signi(_val) (abs(_val) != 0 ? (_val) / fabs(_val) : 1)
#define signf(_val) (fabs(_val) != 0.f ? (_val) / fabs(_val) : 1.f)

	vec3f lastcuberot = cuberot;

	//if(fabs(cuberot.x) > 0.f) cuberot.x += -signf(cuberot.x) * linearStep;
	//if(fabs(cuberot.z) > 0.f) cuberot.z += -signf(cuberot.z) * linearStep;

	cuberot.x += smoothdelta(cuberot.x, 0.f, 8.f);
	cuberot.z += smoothdelta(cuberot.z, 0.f, 8.f);

	if(signf(lastcuberot.x) != signf(cuberot.x)) cuberot.x = 0.f;
	if(signf(lastcuberot.z) != signf(cuberot.z)) cuberot.z = 0.f;

	/*float xds = signf(targetpos.x - cubepos.x);
	float yds = signf(targetpos.y - cubepos.y);

	float xf = (cubepos.x - (long)cubepos.x) * xds;
	float yf = (cubepos.y - (long)cubepos.y) * yds;

	cuberot.x = yf * 90.f;
	cuberot.z = xf * 90.f;*/

	/*cuberot.x = (cubepos.y + 5.f) * 90.f;
	cuberot.z = (cubepos.x + 5.f) * -90.f;*/

	if(Input::isKeyHit(sf::Keyboard::Return))
	{
		std::cout << "HAX\n";
	}

	if(m_introclock.getElapsedTime().asSeconds() > 1.f)
	{
		if(m_victoryState != Victory)
			m_introphase += smoothdelta(m_introphase, 0.f, 30.f);
		
		if(m_victoryState != Undecided)
			m_victoryphase += smoothdelta(m_victoryphase, 1.f, 30.f);
		else
			m_victoryphase += smoothdelta(m_victoryphase, 0.f, 30.f);

		float xdelta = smoothdelta(cubepos.x, targetpos.x, 8.f);
		cubepos.x += xdelta;

		float ydelta = smoothdelta(cubepos.y, targetpos.y, 8.f);
		cubepos.y += ydelta;

		cubepos.z += cubevely * Time.delta;
	}

	//float cubealpha = 2.f - cubepos.z / 2.f + 2.f;
	float cubealpha = (cubepos.z * cubepos.z) / -15.f + 1.f;
	cubealpha = Util::clamp(cubealpha, 0.f, 1.f);

	cube->call("setColor", Color(70, 150, 250, (uint8)(cubealpha * 255.f)));
	cube->call("setRotation", cuberot);

	float ict = m_introclock.getElapsedTime().asSeconds() - 6.f;
	float gtalpha = 2.f - (ict * ict) / 11.f;
	gtalpha = Util::clamp(gtalpha, 0.f, 1.f);

	gametip->call("setPosition", vec3f(4.f, 1.f - m_introphase, -7.4f));
	gametip->call("setColor", Color(255, 255, 255, (uint8)(gtalpha * 255.f)));
	//gametip->call("setRotation", vec3f(65.f, -3.f, 10.f));
	//gametip->call("setScale",    vec3f(2.f, 1.f, 2.f));

	////////////////

	float platformy = 0.f;
	for(std::vector<Spacebox*>::iterator it = boxes.begin(); it != boxes.end(); ++it)
	{
		vec3f pos = (*it)->request<vec3f>("getPosition");

		float x = fabs(pos.x - 5.f) / -10.f;
		float y = fabs(pos.z - 5.f) / -10.f;

		float introy = m_introphase * x * y * 10.f;
		// cos(pos.x * pos.z / 10.f + Time.total) + (0.05f + m_introphase / 8.f) + 
		pos.y = introy;

		//(*it)->call("setColor", Color(255, 255, 255, (uint8)((1.f - m_victoryphase) * 255.f)));
		(*it)->call("setPosition", pos);

		if(platformy < 0.f && fabs(pos.x - cubepos.x) <= 0.05f && fabs(pos.z - cubepos.y) <= 0.05f)
		{
			platformy = pos.y;
		}
	}

	float pcx = cubepos.x + 0.5f;
	float pcy = cubepos.y + 0.5f;

	float turnrise = 0.f;
	turnrise = fabs(cos(pcx * Util::PI)) * 0.23f + fabs(cos(pcy * Util::PI)) * 0.23f;

	cube->call("setPosition", vec3f(cubepos.x, cubepos.z + platformy + 0.5f + turnrise, cubepos.y));

	int x = (int)targetpos.x + 5;
	int y = (int)targetpos.y + 5;

	if(cubepos.z >= 0.f && cubepos.z <= 2.f)
	{
		if(Input::isKeyHit(sf::Keyboard::Left))
		{
			targetpos.x -= 1.f;
			cuberot.z -= 90.f;
		}

		if(Input::isKeyHit(sf::Keyboard::Right))
		{
			targetpos.x += 1.f;
			cuberot.z += 90.f;
		}

		if(Input::isKeyHit(sf::Keyboard::Up))
		{
			targetpos.y -= 1.f;
			cuberot.x	+= 90.f;
		}

		if(Input::isKeyHit(sf::Keyboard::Down))
		{
			targetpos.y	+= 1.f;
			cuberot.x	-= 90.f;
		}
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
			m_victoryState = Victory;
			victoryplane->setEnabled(true);
			failplane->setEnabled(false);
		}

		if(cubepos.z <= -3.f)
		{
			m_victoryState = Loss;
			failplane->setEnabled(true);
			victoryplane->setEnabled(false);
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

	/////////////////////////////////////77
	// Camera positioning

	float cx = std::max(1.f, cubepos.x + 6.f);
	float cy = std::max(1.f, cubepos.y + 6.f);

	float ivp = 1.f - m_victoryphase;

	// Rotation
	camrot.x = 40.f - cy * cy / 20.f;
	camrot.x += 6.f * m_victoryphase;

	camrot.y = -75.f + 5.f * cos(Time.total / 7.f);
	camrot.y += -9.f * m_victoryphase;

	// Position
	campos.x = -3.2f - 0.5f * cos(Time.total / 7.f);
	campos.x += log(cx * cx + m_introphase * 55.f) / 2.f * ivp;
	campos.x += 2.f * m_victoryphase;

	campos.y = 5.5f + sin(Time.total / 9.f) * 0.25f;
	campos.y -= log(cy + 4.f) * 0.8f * ivp;
	campos.y += log(1.f + m_introphase * 50.f) * 0.5f * ivp;
	campos.y += m_victoryphase * 5.6f;

	campos.z = 2.f;
	campos.z += log(cy * cy * 2.f + m_introphase * 505.f) * ivp;
	campos.z += -2.f * m_victoryphase;

	cam->setRotation(camrot);
	cam->setPosition(campos);
}

//////////////////////////////////////////////////////
void TestScene::render()
{
	
}