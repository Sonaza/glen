#include <glen/Game/Skybox.hpp>

#include <glen/System/AssetManager.hpp>
#include <glen/System/Assets/ModelAsset.hpp>

#include <glen/Graphics/Material.hpp>

#include <glen/Game/Components/Transform.hpp>
#include <glen/Game/Components/Renderer.hpp>

#include <glen/Game/Camera.hpp>

using namespace glen;

////////////////////////////////////////////////////
Skybox::Skybox(const std::string &cubemap)
{
	Material* mat = AssetManager::createMaterial(Material::Skybox, cubemap);
	ModelAsset* model = AssetManager::createModel("skybox.obj")->setMaterial(mat);

	m_draworder = 5000;

	Transform* trans = new Transform;
	attachComponent(trans);
	attachComponent(new Renderer(model));

	trans->setScale(5.f, 5.f, 5.f);
}

////////////////////////////////////////////////////
Skybox::~Skybox()
{
	
}

////////////////////////////////////////////////////
void Skybox::update()
{
	call("setPosition", Camera::getCamera()->getPosition());
}