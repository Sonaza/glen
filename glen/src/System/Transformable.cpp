#include <glen/System/Transformable.hpp>

using namespace glen;

//////////////////////////////////////////////////
Transformable::Transformable(void) :
	m_updateMatrix(true),
	m_scale(1.f, 1.f, 1.f)
{
}

//////////////////////////////////////////////////
void Transformable::setPosition(const vec3f& v)
{
	m_position = v;
	m_updateMatrix = true;
}

//////////////////////////////////////////////////
void Transformable::setPosition(float x, float y, float z)
{
	setPosition(vec3f(x, y, z));
}

//////////////////////////////////////////////////
vec3f Transformable::getPosition() const
{
	return m_position;
}

//////////////////////////////////////////////////
void Transformable::move(const vec3f& delta)
{
	m_position += delta;
	m_updateMatrix = true;
}

//////////////////////////////////////////////////
void Transformable::move(float x, float y, float z)
{
	move(vec3f(x, y, z));
}

//////////////////////////////////////////////////
void Transformable::setPivot(const vec3f& v)
{
	m_pivot = v;
	m_updateMatrix = true;
}

//////////////////////////////////////////////////
void Transformable::setPivot(float x, float y, float z)
{
	setPivot(vec3f(x, y, z));
}

//////////////////////////////////////////////////
vec3f Transformable::getPivot() const
{
	return m_pivot;
}

//////////////////////////////////////////////////
void Transformable::setRotation(const vec3f& v)
{
	m_rotation = v;
	m_updateMatrix = true;
}

//////////////////////////////////////////////////
void Transformable::setRotation(float x, float y, float z)
{
	setRotation(vec3f(x, y, z));
}

//////////////////////////////////////////////////
vec3f Transformable::getRotation() const
{
	return m_rotation;
}

//////////////////////////////////////////////////
void Transformable::setScale(const vec3f& v)
{
	m_scale = v;
	m_updateMatrix = true;
}

//////////////////////////////////////////////////
void Transformable::setScale(float x, float y, float z)
{
	setScale(vec3f(x, y, z));
}

//////////////////////////////////////////////////
vec3f Transformable::getScale() const
{
	return m_scale;
}

//////////////////////////////////////////////////
mat4 Transformable::getMatrix()
{
	if(m_updateMatrix)
	{
		m_matrix = mat4();
		m_matrix.translate(m_position)
			.rotate(m_rotation.x, vec3f(1.f, 0.f, 0.f))
			.rotate(m_rotation.y, vec3f(0.f, 1.f, 0.f))
			.rotate(m_rotation.z, vec3f(0.f, 0.f, 1.f))
			.translate(m_pivot)
			.scale(m_scale);

		m_updateMatrix = false;
	}

	return m_matrix;
}
