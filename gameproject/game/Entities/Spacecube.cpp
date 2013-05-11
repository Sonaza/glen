#include <game/Entities/Spacecube.hpp>

#include <glen/System/AssetManager.hpp>
#include <glen/System/Assets/ModelAsset.hpp>

#include <glen/Game/Components/Transform.hpp>
#include <glen/Game/Components/Renderer.hpp>

#include <glen/System/Utility.hpp>

using namespace glen;

///////////////////////////////////////////////////
Spacecube::Spacecube()
{
	AssetManager::loadTexture2D("cube", "cube.png");
	Material* mat = AssetManager::createMaterial(Material::Diffuse, "cube");
	
	int c = Util::random_int(100, 230);
	mat->setColor(100, c/1.5f, c);

	ModelAsset* model = AssetManager::createModel("cube.obj")
		->setMaterial(mat);

	t = new Transform;

	t->setPivot(0.f, -0.5f, 0.f);

	// Create new entity and attach transform and renderer
	attachComponent(t);
	attachComponent(new Renderer(model));

	float s = Util::random_float(0.5f, 1.5f);

	t->setScale(s, s, s);

	vec3f pos(
		Util::random_float(-50.f, 70.f),
		Util::random_float(-35.f, 10.f),
		-15.f + Util::random_float(-80.f, 5.f)
	);

	vec3f rot(
		Util::random_float(-180.f, 180.f),
		Util::random_float(-180.f, 180.f),
		Util::random_float(-180.f, 180.f)
	);

	t->setPosition(pos);
	t->setRotation(rot);

	rotvel = vec3f(
		Util::random_float(-30.f, 30.f),
		Util::random_float(-30.f, 30.f),
		Util::random_float(-30.f, 30.f)
	);

	offset = Util::random_float(0.f, 5.f);
}

///////////////////////////////////////////////////
Spacecube::~Spacecube()
{

}

///////////////////////////////////////////////////
void Spacecube::update()
{
	float delta = deltaclock.restart().asSeconds();

	vec3f rot = t->getRotation();

	rot.x += rotvel.x * delta;
	rot.x += rotvel.y * delta;
	rot.z -= rotvel.z * delta;

	t->setRotation(rot);

	vec3f pos = t->getPosition();
	pos.y += cos(totalclock.getElapsedTime().asSeconds() * 5.f + offset) / 5.f * delta;

	t->setPosition(pos);
}

