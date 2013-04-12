#include <glen/Game/Components/Transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glen;

////////////////////////////////////////////////////
Transform::Transform() : Component("transform"),
	m_position(0.f, 0.f, 0.f),
	m_pivot(0.f, 0.f, 0.f),
	m_rotation(0.f, 0.f, 0.f),
	m_scale(1.f, 1.f, 1.f),
	m_updateMatrix(true)
{
	
}

////////////////////////////////////////////////////
Transform::~Transform()
{
}

////////////////////////////////////////////////////
void Transform::attached()
{
	listen("setPosition",	&Transform::setPosition);
	listen("setPivot",		&Transform::setPivot);
	listen("setRotation",	&Transform::setRotation);
	listen("setScale",		&Transform::setScale);

	listen("getPosition",	&Transform::getPositionRequest);
	listen("getPivot",		&Transform::getPivotRequest);
	listen("getRotation",	&Transform::getRotationRequest);
	listen("getScale",		&Transform::getScaleRequest);

	listen("getMatrix",		&Transform::getMatrixRequest);
}

////////////////////////////////////////////////////
void Transform::setPosition(const Vector3f &v)
{
	m_position = v;
}

////////////////////////////////////////////////////
void Transform::setPosition(float x, float y, float z)
{
	setPosition(Vector3f(x, y, z));
}

////////////////////////////////////////////////////
void Transform::setPosition(const Message &msg)
{
	assert(msg.data.type() == typeid(Vector3f) && "Wrong data type");
	setPosition(boost::any_cast<Vector3f>(msg.data));
}

////////////////////////////////////////////////////
void Transform::setPivot(const Vector3f &v)
{
	m_pivot = v;
}

////////////////////////////////////////////////////
void Transform::setPivot(float x, float y, float z)
{
	setPivot(Vector3f(x, y, z));
}

////////////////////////////////////////////////////
void Transform::setPivot(const Message &msg)
{
	assert(msg.data.type() == typeid(Vector3f) && "Wrong data type");
	setPivot(boost::any_cast<Vector3f>(msg.data));
}

////////////////////////////////////////////////////
void Transform::setRotation(const Vector3f &v)
{
	m_rotation = v;
}

////////////////////////////////////////////////////
void Transform::setRotation(float x, float y, float z)
{
	m_rotation = Vector3f(x, y, z);
}

////////////////////////////////////////////////////
void Transform::setRotation(const Message &msg)
{
	assert(msg.data.type() == typeid(Vector3f) && "Wrong data type");
	setRotation(boost::any_cast<Vector3f>(msg.data));
}

////////////////////////////////////////////////////
void Transform::setScale(const Vector3f &v)
{
	m_scale = v;
}

////////////////////////////////////////////////////
void Transform::setScale(float x, float y, float z)
{
	setScale(Vector3f(x, y, z));
}

////////////////////////////////////////////////////
void Transform::setScale(const Message &msg)
{
	assert(msg.data.type() == typeid(Vector3f) && "Wrong data type");
	setScale(boost::any_cast<Vector3f>(msg.data));
}

////////////////////////////////////////////////////
glm::mat4 Transform::getMatrix()
{
	if(m_updateMatrix)
	{
		m_matrix = glm::mat4(1.f);

		m_matrix = glm::translate(m_matrix, glm::vec3(m_position.x, m_position.y, m_position.z));

		m_matrix = glm::rotate(m_matrix, m_rotation.x, glm::vec3(1.f, 0.f, 0.f));
		m_matrix = glm::rotate(m_matrix, m_rotation.y, glm::vec3(0.f, 1.f, 0.f));
		m_matrix = glm::rotate(m_matrix, m_rotation.z, glm::vec3(0.f, 0.f, 1.f));

		m_matrix = glm::translate(m_matrix, glm::vec3(m_pivot.x, m_pivot.y, m_pivot.z));

		m_matrix = glm::scale(m_matrix, glm::vec3(m_scale.x, m_scale.y, m_scale.z));

		m_updateMatrix = false;
	}

	return m_matrix;
}
