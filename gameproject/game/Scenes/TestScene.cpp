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
	cam = new Camera(80.f, 1.f, 1000.f);
	World::addEntity(cam);

	{
		AssetManager::loadTextureCubemap("skybox", "sky/left.png", "sky/right.png", "sky/top.png", "sky/bottom.png", "sky/front.png", "sky/back.png");

		skybox = new Skybox;
		skybox->loadSkybox("skybox");

		World::addEntity(skybox);
	}

	level.resize(121, 1);
	level[45] = 0;

	for(int i=0; i < 121; ++i)
	{
		if(level[i] == 0) continue;
		
		int x = i % 11 - 5;
		int y = (int)floor(i / 11.f) - 5;

		Spacebox* box = new Spacebox;
		box->m_draworder = 10000;

		box->call("setScale", vec3f(1.f, 1.f, 1.f));
		box->call("setPosition", vec3f(x, 0.f, y));

		World::addEntity(box);

		boxes.push_back(box);
	}

	/*for(int y = -5; y <= 5; ++y)
	{
		for (int x = -5; x <= 5; ++x)
		{
			Spacebox* box = new Spacebox;
			box->m_draworder = 10000;

			box->call("setScale", vec3f(1.f, 1.f, 1.f));
			box->call("setPosition", vec3f(x, 0.f, y));

			World::addEntity(box);

			boxes.push_back(box);
		}
	}*/

	velforward = 0.f;
	
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

	/*for(std::vector<Spacebox*>::iterator it = boxes.begin(); it != boxes.end(); ++it)
	{
		Spacebox* b = *it;
		vec3f p = b->request<vec3f>("getPosition");

		b->call("setPosition",
			vec3f(p.x,
			0.f + cos(p.x * p.z / 23.f + Time.total * 2.f),
			p.z));
	}*/

	camrot.y += diff.x / (2.f * center.x) * 330.f;
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
	}

	cam->setRotation(camrot);

	float yrad = camrot.y * 3.141592f / 180.f;

	float multi = 1.5f; //(campos.y + 0.f) / 10.f + (Input::isMouseDown(sf::Mouse::Right) ? 5.f : 0.f);

	if(Input::isKeyDown(sf::Keyboard::Space))// && campos.y <= 2.1f)
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
	}

	cam->setPosition(campos);
}

//////////////////////////////////////////////////////
void TestScene::render()
{
	
}