#include <glen/Game/Skybox.hpp>

#include <glen/System/AssetManager.hpp>
#include <glen/System/Assets/ModelAsset.hpp>

#include <glen/Graphics/Material.hpp>

#include <glen/Game/Components/Transform.hpp>
#include <glen/Game/Components/Renderer.hpp>

#include <glen/Game/Camera.hpp>

using namespace glen;

////////////////////////////////////////////////////
Skybox::Skybox()
{
	
}

////////////////////////////////////////////////////
Skybox::~Skybox()
{
	
}

////////////////////////////////////////////////////
void Skybox::loadSkybox(const std::string &cubemap)
{
	Material* mat = AssetManager::createMaterial(Material::Skybox, cubemap);

	AssetManager::loadModel("skybox", "skybox.obj")->setMaterial(mat);

	m_draworder = 9999;
	Transform* trans = new Transform;
	attachComponent(trans);
	attachComponent(new Renderer("skybox"));

	trans->setScale(5.f, 5.f, 5.f);
}

////////////////////////////////////////////////////
void Skybox::update()
{
	call("setPosition", Camera::getCamera()->getPosition());
}