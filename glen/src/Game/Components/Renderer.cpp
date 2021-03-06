#include <glen/Game/Components/Renderer.hpp>

#include <glen/System/AssetManager.hpp>
#include <glen/System/Assets/ModelAsset.hpp>

using namespace glen;

////////////////////////////////////////////////////
Renderer::Renderer() : Component("renderer"),
	m_model(NULL)
{
	
}

////////////////////////////////////////////////////
Renderer::Renderer(ModelAsset* model) : Component("renderer"),
	m_model(NULL)
{
	setModel(model);
}

////////////////////////////////////////////////////
Renderer::~Renderer()
{
	
}

////////////////////////////////////////////////////
void Renderer::attached()
{
	m_entity->m_drawable = true;

	listen("setColor", &Renderer::setColor);

	listen("draw", &Renderer::draw);
}

////////////////////////////////////////////////////
void Renderer::update()
{
	m_transform = request<mat4>("getMatrix");
}

////////////////////////////////////////////////////
void Renderer::setModel(ModelAsset* model)
{
	assert(model);
	m_model = model->getAsset();
}

////////////////////////////////////////////////////
void Renderer::setColor(const Message &msg)
{
	assert(m_model);
	assert(msg.data.type() == typeid(Color) && "Wrong data type");
	m_model->m_material->setColor(boost::any_cast<Color>(msg.data));
}

////////////////////////////////////////////////////
void Renderer::draw(const Message &msg)
{
	assert(m_model != NULL && "Model has not been set");
	m_model->render(m_transform);
}

