#ifndef GLEN_RENDERER_HPP
#define GLEN_RENDERER_HPP

#include <glen/Game/Component.hpp>
#include <glen/Graphics/Model.hpp>

#include <glen/System/Types.hpp>

#include <string>
#include <memory>

namespace glen
{

	class ModelAsset;

	class Renderer : public Component
	{
	public:
		Renderer();
		Renderer(ModelAsset* model);
		~Renderer();

		void attached();
		void update();

		void setModel(ModelAsset* model);

		void draw(const Message &msg);

	private:
		
		Model*		m_model;
		mat4	m_transform;

	};
	
}

#endif GLEN_RENDERER_HPP
