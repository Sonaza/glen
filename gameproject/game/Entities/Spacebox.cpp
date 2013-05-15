#include <game/Entities/Spacebox.hpp>

#include <glen/System/AssetManager.hpp>
#include <glen/System/Assets/ModelAsset.hpp>

#include <glen/Game/Components/Transform.hpp>
#include <glen/Game/Components/Renderer.hpp>

using namespace glen;

///////////////////////////////////////////////////
Spacebox::Spacebox(const int c)
{
	// Create new diffuse material
	Material* mat;

	switch(c)
	{
	case 0:
	case 3:
		AssetManager::loadTexture2D("spacebox_n", "spacebox.png");
		mat = AssetManager::createMaterial(Material::SpecularDiffuse, "spacebox_n");
		break;
	case 1:
		AssetManager::loadTexture2D("spacebox_y", "spaceboxy.png");
		mat = AssetManager::createMaterial(Material::SpecularDiffuse, "spacebox_y");
		break;
	case 2:
		AssetManager::loadTexture2D("spacebox_g", "spaceboxg.png");
		mat = AssetManager::createMaterial(Material::SpecularDiffuse, "spacebox_g");
		break;
	}

	m_type = c;

	// Load bunny model and apply the material
	ModelAsset* model = AssetManager::createModel("spacebox.obj")
		->setMaterial(mat);

	// Create new entity and attach transform and renderer
	attachComponent(new Transform);
	attachComponent(new Renderer(model));
}

///////////////////////////////////////////////////
Spacebox::~Spacebox()
{

}

///////////////////////////////////////////////////
void Spacebox::update()
{

}
