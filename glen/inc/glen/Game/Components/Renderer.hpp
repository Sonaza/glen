#ifndef GLEN_RENDERER_HPP
#define GLEN_RENDERER_HPP

#include <glen/Game/Component.hpp>
#include <glen/Graphics/Model.hpp>

#include <glm/glm.hpp>

#include <string>
#include <memory>

namespace glen
{

	class Renderer : public Component
	{
	public:
		Renderer();
		Renderer(const std::string &modelID);
		~Renderer();

		void attached();
		void update();

		void setModel(const std::string &assetID);

		void draw(const Message &msg);

	private:
		
		Model*		m_model;
		glm::mat4	m_transform;

	};
	
}

#endif GLEN_RENDERER_HPP
