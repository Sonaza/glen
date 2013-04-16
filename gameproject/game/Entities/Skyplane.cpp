#include <game/Entities/Skyplane.hpp>

//////////////////////////////////////////////////////
Skyplane::Skyplane(const std::string &texture, Vector3f rot)
{
	AssetManager::loadTexture2D(texture, texture)
		->getAsset()
		->setClamping(Texture2D::Settings::Clamp);

	// Create new diffuse material
	Material* mat = MaterialFactory::skyplane(texture);
	AssetManager::createMaterial(texture, mat);

	// Apply some scaling to the diffuse texture
	//mat->getTransform<Texture2D::Diffuse>()->setScale(15.f, 15.f, 1.f);

	// Load bunny model and apply the material
	AssetManager::loadModel(texture, "skyplane.obj")
		->setMaterial(texture);

	// Create new entity and attach transform and renderer
	attachComponent(new Transform);
	attachComponent(new Renderer(texture));

	send("setScale", Vector3f(500.f, 500.f, 500.f));
	send("setPosition", Vector3f(0.f, 5.f, 0.f));
	send("setRotation", rot);

	// Send the entity to the world pipeline
	World::addEntity(this);
}

//////////////////////////////////////////////////////
Skyplane::~Skyplane(void)
{
}