#include <glen/Game/Components/Transform.hpp>
#include <iostream>

using namespace glen;

////////////////////////////////////////////////////
Transform::Transform() : Component("transform"),
	m_position(0.f, 0.f),
	m_rotation(0.f),
	m_scale(1.f, 1.f)
{
	
}

////////////////////////////////////////////////////
Transform::~Transform()
{
	
}

////////////////////////////////////////////////////
void Transform::attached()
{
	listen("setPosition", &Transform::setPosition);
	listen("setRotation", &Transform::setRotation);
	listen("setScale", &Transform::setScale);

	listen("getPosition", &Transform::getPositionRequest);
	listen("getRotation", &Transform::getRotationRequest);
	listen("getScale", &Transform::getScaleRequest);
}

////////////////////////////////////////////////////
void Transform::setPosition(Vector2f v)
{
	v.y = -v.y;
	m_position = v;
}

////////////////////////////////////////////////////
void Transform::setPosition(float x, float y)
{
	setPosition(Vector2f(x, y));
}

////////////////////////////////////////////////////
void Transform::setPosition(const Message &msg)
{
	setPosition(boost::any_cast<Vector2f>(msg.data));
}

////////////////////////////////////////////////////
void Transform::move(Vector2f v)
{
	m_position += v;
}

////////////////////////////////////////////////////
void Transform::move(float x, float y)
{
	move(Vector2f(x, y));
}

////////////////////////////////////////////////////
void Transform::setRotation(float a)
{
	m_rotation = a;
}

////////////////////////////////////////////////////
void Transform::rotate(float a)
{
	m_rotation += a;
}

////////////////////////////////////////////////////
void Transform::setRotation(const Message &msg)
{
	setRotation(boost::any_cast<float>(msg.data));
}

////////////////////////////////////////////////////
void Transform::setScale(Vector2f v)
{
	m_scale = v;
}

////////////////////////////////////////////////////
void Transform::setScale(float x, float y)
{
	setScale(Vector2f(x, y));
}

////////////////////////////////////////////////////
void Transform::setScale(const Message &msg)
{
	setScale(boost::any_cast<Vector2f>(msg.data));
}