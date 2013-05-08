#include <game/Entities/Skyplane.hpp>

//////////////////////////////////////////////////////
Skyplane::Skyplane(const std::string &texture, vec3f rot)
{
	AssetManager::loadTexture2D(texture, texture)
		->getAsset()
		->setClamping(Texture::Clamp);

	// Create new diffuse material
	Material* mat = AssetManager::createMaterial(Material::Skyplane, texture);

	// Apply some scaling to the diffuse texture
	//mat->getTransform<Texture2D::Diffuse>()->setScale(15.f, 15.f, 1.f);

	// Load bunny model and apply the material
	AssetManager::loadModel(texture, "skyplane.obj")
		->setMaterial(mat);

	// Create new entity and attach transform and renderer
	attachComponent(new Transform);
	attachComponent(new Renderer(texture));

	call("setScale", vec3f(1500.f, 1500.f, 1500.f));
	call("setPosition", vec3f(0.f, 5.f, 0.f));
	call("setRotation", rot);

	// Send the entity to the world pipeline
	World::addEntity(this);
}

//////////////////////////////////////////////////////
Skyplane::~Skyplane(void)
{
}
