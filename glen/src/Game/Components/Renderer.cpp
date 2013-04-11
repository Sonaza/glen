#include <glen/Game/Components/Renderer.hpp>

/*#include <glen/System/AssetManager.hpp>*/

#include <glen/Graphics/Camera.hpp>

using namespace glen;

////////////////////////////////////////////////////
Renderer::Renderer() :
	Component("renderer")
{
	
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
	Vector2f position = request<Vector2f>("getPosition");
	//position += Camera::getCameraOffset();

	/*m_sprite->setPosition(position);
	m_sprite->setRotation(request<float>("getRotation"));
	m_sprite->setScale(request<Vector2f>("getScale"));*/
}

////////////////////////////////////////////////////
void Renderer::setModel(const std::string &assetID)
{
	/*TextureAsset* asset = AssetManager::getTexture(assetID);

	if(asset)
	{
		m_sprite.reset(new sf::Sprite(*asset->getAsset()));

		// Set sprite's origin point in the center
		m_sprite->setOrigin(
			static_cast<Vector2f>(asset->getAsset()->getSize()) / 2.f
		);
	}*/
}

////////////////////////////////////////////////////
void Renderer::draw(const Message &msg)
{
	//assert(!msg.data.empty());
	//boost::any_cast<sf::RenderWindow*>(msg.data)->draw(*m_sprite, m_renderStates);
}