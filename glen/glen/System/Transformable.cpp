#include <glen/System/Transformable.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace glen
{

//////////////////////////////////////////////////
Transformable::Transformable(void) :
	m_updateMatrix(true),
	m_scale(1.f, 1.f, 1.f)
{
}

//////////////////////////////////////////////////
void Transformable::setPosition(const Vector3f& v)
{
	m_position = v;
	m_updateMatrix = true;
}

//////////////////////////////////////////////////
void Transformable::setPosition(float x, float y, float z)
{
	setPosition(Vector3f(x, y, z));
}

//////////////////////////////////////////////////
Vector3f Transformable::getPosition() const
{
	return m_position;
}

//////////////////////////////////////////////////
void Transformable::setRotation(const Vector3f& v)
{
	m_rotation = v;
	m_updateMatrix = true;
}

//////////////////////////////////////////////////
void Transformable::setRotation(float x, float y, float z)
{
	setRotation(Vector3f(x, y, z));
}

//////////////////////////////////////////////////
Vector3f Transformable::getRotation() const
{
	return m_rotation;
}

//////////////////////////////////////////////////
void Transformable::setScale(const Vector3f& v)
{
	m_scale = v;
	m_updateMatrix = true;
}

//////////////////////////////////////////////////
void Transformable::setScale(float x, float y, float z)
{
	setScale(Vector3f(x, y, z));
}

//////////////////////////////////////////////////
Vector3f Transformable::getScale() const
{
	return m_scale;
}

//////////////////////////////////////////////////
glm::mat4 Transformable::getMatrix()
{
	if(m_updateMatrix)
	{
		m_matrix = glm::mat4(1.f);
		m_matrix = glm::rotate(m_matrix, m_rotation.x, glm::vec3(1.f, 0.f, 0.f));
		m_matrix = glm::rotate(m_matrix, m_rotation.y, glm::vec3(0.f, 1.f, 0.f));
		m_matrix = glm::rotate(m_matrix, m_rotation.z, glm::vec3(0.f, 0.f, 1.f));

		m_matrix = glm::translate(m_matrix, glm::vec3(m_position.x, m_position.y, m_position.z));

		m_matrix = glm::scale(m_matrix, glm::vec3(m_scale.x, m_scale.y, m_scale.z));

		m_updateMatrix = false;
	}

	return m_matrix;
}

}