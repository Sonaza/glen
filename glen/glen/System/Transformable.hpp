#ifndef GLEN_TRANSFORMABLE_HPP
#define GLEN_TRANSFORMABLE_HPP

#include <glm/glm.hpp>
#include <glen/System/Vector3.hpp>

namespace glen
{

	class Transformable
	{
	public:
		Transformable(void);

		void setPosition(const Vector3f& v);
		void setPosition(float x, float y, float z);
		Vector3f getPosition() const;

		void setRotation(const Vector3f& v);
		void setRotation(float x, float y, float z);
		Vector3f getRotation() const;

		void setScale(const Vector3f& v);
		void setScale(float x, float y, float z);
		Vector3f getScale() const;

		glm::mat4& getMatrix();
		
	private:

		Vector3f	m_position;
		Vector3f	m_rotation;
		Vector3f	m_scale;

		bool		m_updateMatrix;
		glm::mat4	m_matrix;

	};

}

#endif
