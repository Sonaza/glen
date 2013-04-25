#include <glen/Game/Components/Renderer.hpp>

#include <glen/System/AssetManager.hpp>
#include <glen/System/Assets/ModelAsset.hpp>

#include <glen/Graphics/Camera.hpp>

using namespace glen;

////////////////////////////////////////////////////
Renderer::Renderer() :
	Component("renderer"),
	m_model(NULL)
{
	
}

////////////////////////////////////////////////////
Renderer::Renderer(const std::string &modelID) :
	Component("renderer"),
	m_model(NULL)
{
	setModel(modelID);
}

////////////////////////////////////////////////////
Renderer::~Renderer()
{
	
}

////////////////////////////////////////////////////
void Renderer::attached()
{
	listen("draw", &Renderer::draw);
}

////////////////////////////////////////////////////
void Renderer::update()
{
	m_transform = request<mat4>("getMatrix");
}

////////////////////////////////////////////////////
void Renderer::setModel(const std::string &assetID)
{
	ModelAsset* asset = AssetManager::getModel(assetID);

	if(asset)
	{
		m_model = asset->getAsset();
	}
}

////////////////////////////////////////////////////
void Renderer::draw(const Message &msg)
{
	assert(m_model != NULL && "Model has not been set");
	m_model->render(m_transform);
}