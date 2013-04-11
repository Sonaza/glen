#ifndef GLEN_PHYSICS_HPP
#define GLEN_PHYSICS_HPP

#include <glen/Game/Component.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>

#include <Box2D/Box2D.h>

namespace glen
{
	
	class Physics : public Component
	{
	public:
		Physics();
		~Physics();
		
		void attached();
		void update();

		void uninit(const Message &msg);

		void setPosition(sf::Vector2f v);
		void setPosition(const Message &msg);

		void setRotation(float a);
		void setRotation(const Message &msg);

		inline b2Body* getBody() const { return m_body; }

		enum BodyType
		{
			Static		= b2_staticBody,
			Dynamic		= b2_dynamicBody,
			Kinematic	= b2_kinematicBody,
		};

		// Creates a box body
		void createBox(sf::Vector2f size, BodyType type = Dynamic);
		void createBox(float sx, float sy, BodyType type = Dynamic);

		// Creates a circle body
		void createCircle(float radius, BodyType type = Dynamic);

		// Creates a body from vertices
		void createPolygon(std::vector<sf::Vector2f> vertices, BodyType type = Dynamic);

		// Set's rest of the body's properties
		void finalizeBody(float friction, float restitution, float density);

	protected:
		
		float		m_worldScale;

		b2Body*		m_body;
		b2World*	p_world;

		b2BodyDef		m_bodyDef;

		struct b2ShapeStruct
		{
			b2PolygonShape	polygon;
			b2CircleShape	circle;
		} m_bodyShape;

		b2FixtureDef	m_fixtureDef;

	private:

		void _createBody(BodyType type);

	};
	
}

#endif GLEN_PHYSICS_HPP
