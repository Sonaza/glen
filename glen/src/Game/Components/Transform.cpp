#include <glen/Game/Components/Transform.hpp>

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
void Transform::setPosition(const vec3f &v)
{
	m_position = v;
	m_updateMatrix = true;
}

////////////////////////////////////////////////////
void Transform::setPosition(float x, float y, float z)
{
	setPosition(vec3f(x, y, z));
}

////////////////////////////////////////////////////
void Transform::setPosition(const Message &msg)
{
	assert(msg.data.type() == typeid(vec3f) && "Wrong data type");
	setPosition(boost::any_cast<vec3f>(msg.data));
}

////////////////////////////////////////////////////
void Transform::setPivot(const vec3f &v)
{
	m_pivot = v;
	m_updateMatrix = true;
}

////////////////////////////////////////////////////
void Transform::setPivot(float x, float y, float z)
{
	setPivot(vec3f(x, y, z));
}

////////////////////////////////////////////////////
void Transform::setPivot(const Message &msg)
{
	assert(msg.data.type() == typeid(vec3f) && "Wrong data type");
	setPivot(boost::any_cast<vec3f>(msg.data));
}

////////////////////////////////////////////////////
void Transform::setRotation(const vec3f &v)
{
	m_rotation = v;
	m_updateMatrix = true;
}

////////////////////////////////////////////////////
void Transform::setRotation(float x, float y, float z)
{
	setRotation(vec3f(x, y, z));
}

////////////////////////////////////////////////////
void Transform::setRotation(const Message &msg)
{
	assert(msg.data.type() == typeid(vec3f) && "Wrong data type");
	setRotation(boost::any_cast<vec3f>(msg.data));
}

////////////////////////////////////////////////////
void Transform::setScale(const vec3f &v)
{
	m_scale = v;
	m_updateMatrix = true;
}

////////////////////////////////////////////////////
void Transform::setScale(float x, float y, float z)
{
	setScale(vec3f(x, y, z));
}

////////////////////////////////////////////////////
void Transform::setScale(const Message &msg)
{
	assert(msg.data.type() == typeid(vec3f) && "Wrong data type");
	setScale(boost::any_cast<vec3f>(msg.data));
}

////////////////////////////////////////////////////
mat4 Transform::getMatrix()
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
