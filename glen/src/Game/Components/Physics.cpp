#include <glen/Game/Components/Physics.hpp>

#include <glen/Game/Entity.hpp>
#include <glen/Game/Components/Transform.hpp>

#include <glen/Game/World.hpp>
#include <glen/System/ErrorStream.hpp>

#include <iostream>

using namespace glen;

////////////////////////////////////////////////////
Physics::Physics() :
	Component("physics"),
	m_body(NULL),
	p_world(NULL),
	m_worldScale(1.f)
{
	
}

////////////////////////////////////////////////////
Physics::~Physics()
{
	if(p_world && m_body)
	{
		p_world->DestroyBody(m_body);
	}
}

////////////////////////////////////////////////////
void Physics::attached()
{
	assert(m_entity->hasComponent("transform"));

	p_world = World::getBox2DWorld();
	m_worldScale = World::getWorldScale();
}

////////////////////////////////////////////////////
void Physics::_createBody(BodyType type)
{
	assert(m_entity && "Component has not been attached");

	m_bodyDef.type = static_cast<b2BodyType>(type);

	Transform* transform = m_entity->getComponent<Transform>("transform");
	sf::Vector2f position = transform->getPosition() / m_worldScale;

	m_bodyDef.position.Set(position.x, position.y);
	m_bodyDef.angle = transform->getRotation() * b2_pi / 180.f;

	m_body = p_world->CreateBody(&m_bodyDef);

	// Rgister the callbacks since body is now created
	listen("setPosition", &Physics::setPosition);
	listen("setRotation", &Physics::setRotation);
}

////////////////////////////////////////////////////
void Physics::createBox(sf::Vector2f size, BodyType type)
{
	_createBody(type);
	
	Transform* transform = m_entity->getComponent<Transform>("transform");
	sf::Vector2f scale = transform->getScale();

	// Create box shape scaled according to the world scale
	m_bodyShape.polygon.SetAsBox(
		(size.x - 2.f) / m_worldScale * scale.x * 0.5f,
		(size.y - 2.f) / m_worldScale * scale.y * 0.5f);

	m_fixtureDef.shape = &m_bodyShape.polygon;
}

////////////////////////////////////////////////////
void Physics::createBox(float sx, float sy, BodyType type)
{
	createBox(sf::Vector2f(sx, sy), type);
}

////////////////////////////////////////////////////
void Physics::createCircle(float radius, BodyType type)
{
	_createBody(type);

	Transform* transform = m_entity->getComponent<Transform>("transform");
	sf::Vector2f scale = transform->getScale();

	// Set circle shape radius and relative position to body
	m_bodyShape.circle.m_radius = radius / m_worldScale * scale.x;
	m_bodyShape.circle.m_p.Set(0.f, 0.f);

	m_fixtureDef.shape = &m_bodyShape.circle;
}

////////////////////////////////////////////////////
void Physics::createPolygon(std::vector<sf::Vector2f> vertices, BodyType type)
{
	_createBody(type);

	Transform* transform = m_entity->getComponent<Transform>("transform");
	sf::Vector2f scale = transform->getScale();

	// Create a temporary array for vertices and copy them over
	std::vector<b2Vec2> temp;
	std::for_each(
		vertices.begin(), vertices.end(),
		[&temp, &scale, this](sf::Vector2f p)
		{
			temp.push_back(b2Vec2(p.x / m_worldScale * scale.x, p.y / m_worldScale * scale.y));
		});

	// Set polygon vertices
	m_bodyShape.polygon.Set(&temp[0], temp.size());

	m_fixtureDef.shape = &m_bodyShape.polygon;
}

////////////////////////////////////////////////////
void Physics::finalizeBody(float friction, float restitution, float density)
{
	m_fixtureDef.friction		= friction;
	m_fixtureDef.restitution	= restitution;
	m_fixtureDef.density		= density;

	// Set user data to point back to our parent entity
	// in case we need to do something directly with it
	m_fixtureDef.userData = m_entity;

	// Apply the fixture to the body and we're golden
	m_body->CreateFixture(&m_fixtureDef);
}

////////////////////////////////////////////////////
void Physics::update()
{
	b2Vec2 temp = m_body->GetPosition();

	send("setPosition", sf::Vector2f(temp.x * m_worldScale, -temp.y * m_worldScale));
	send("setRotation", m_body->GetAngle() * 180.f / b2_pi);
}

////////////////////////////////////////////////////
void Physics::setPosition(sf::Vector2f v)
{
	b2Vec2 vec(v.x / m_worldScale, -v.y / m_worldScale);
	m_body->SetTransform(vec, m_body->GetAngle());
}

////////////////////////////////////////////////////
void Physics::setPosition(const Message &msg)
{
	setPosition(boost::any_cast<sf::Vector2f>(msg.data));
}

////////////////////////////////////////////////////
void Physics::setRotation(float a)
{
	m_body->SetTransform(m_body->GetPosition(), a * b2_pi / 180.f);
}

////////////////////////////////////////////////////
void Physics::setRotation(const Message &msg)
{
	setRotation(boost::any_cast<float>(msg.data));
}
