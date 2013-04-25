#ifndef GLEN_TRANSFORMABLE_HPP
#define GLEN_TRANSFORMABLE_HPP

#include <glen/System/Types.hpp>


namespace glen
{

	class Transformable
	{
	public:
		Transformable(void);

		void setPosition(const vec3f& v);
		void setPosition(float x, float y, float z);
		vec3f getPosition() const;

		void move(const vec3f& delta);
		void move(float x, float y, float z);

		void setPivot(const vec3f& v);
		void setPivot(float x, float y, float z);
		vec3f getPivot() const;

		void setRotation(const vec3f& v);
		void setRotation(float x, float y, float z);
		vec3f getRotation() const;

		void setScale(const vec3f& v);
		void setScale(float x, float y, float z);
		vec3f getScale() const;

		virtual mat4 getMatrix();
		
	protected:

		vec3f	m_position;
		vec3f	m_pivot;
		vec3f	m_rotation;
		vec3f	m_scale;

		bool		m_updateMatrix;
		mat4	m_matrix;

	};

}

#endif
