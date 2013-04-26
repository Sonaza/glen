#ifndef GLEN_TRANSFORM_HPP
#define GLEN_TRANSFORM_HPP

#include <glen/System/Types.hpp>
#include <glen/Game/Component.hpp>

namespace glen
{

	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		void attached();

		void setPosition(const vec3f &v);
		void setPosition(float x, float y, float z);
		void setPosition(const Message &msg);
		inline vec3f getPosition() const { return m_position; }

		void setPivot(const vec3f& v);
		void setPivot(float x, float y, float z);
		void setPivot(const Message &msg);
		inline vec3f getPivot() const;

		void setRotation(const vec3f &v);
		void setRotation(float x, float y, float z);
		void setRotation(const Message &msg);
		inline vec3f getRotation() const { return m_rotation; }

		void setScale(const vec3f &v);
		void setScale(float x, float y, float z);
		void setScale(const Message &msg);
		inline vec3f getScale() const { return m_scale; }

		mat4 getMatrix();

	private:

		inline boost::any getPositionRequest()	{ return m_position; }
		inline boost::any getPivotRequest()		{ return m_position; }
		inline boost::any getRotationRequest()	{ return m_rotation; }
		inline boost::any getScaleRequest()		{ return m_scale; }
		inline boost::any getMatrixRequest()	{ return getMatrix(); }
		
		vec3f	m_position;
		vec3f	m_pivot;
		vec3f	m_rotation;
		vec3f	m_scale;

		bool	m_updateMatrix;
		mat4	m_matrix;

	};

}

#endif GLEN_TRANSFORM_HPP
