#ifndef GLEN_TRANSFORM_HPP
#define GLEN_TRANSFORM_HPP

#include <glen/Game/Component.hpp>
#include <glen/System/Vector2.hpp>

namespace glen
{

	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		void attached();

		void setPosition(Vector2f v);
		void setPosition(float x, float y);
		void setPosition(const Message &msg);

		Vector2f getPosition() const { return m_position; }

		void move(Vector2f v);
		void move(float x, float y);

		void setRotation(float a);
		void rotate(float a);
		void setRotation(const Message &msg);

		float getRotation() const { return m_rotation; }

		void setScale(Vector2f v);
		void setScale(float x, float y);
		void setScale(const Message &msg);

		Vector2f getScale() const { return m_scale; }

	private:

		boost::any getPositionRequest() { return m_position; }
		boost::any getRotationRequest() { return m_rotation; }
		boost::any getScaleRequest() { return m_scale; }

		Vector2f	m_position;
		float		m_rotation;
		Vector2f	m_scale;

	};

}

#endif GLEN_TRANSFORM_HPP
