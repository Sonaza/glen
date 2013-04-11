#ifndef GLEN_RENDERER_HPP
#define GLEN_RENDERER_HPP

#include <glen/Game/Component.hpp>
#include <glen/System/Vector2.hpp>

#include <string>
#include <memory>

namespace glen
{

	class Renderer : public Component
	{
	public:
		Renderer();
		~Renderer();

		void attached();
		void update();

		void setModel(const std::string &assetID);

		void draw(const Message &msg);

	private:
		


	};
	
}

#endif GLEN_RENDERER_HPP
