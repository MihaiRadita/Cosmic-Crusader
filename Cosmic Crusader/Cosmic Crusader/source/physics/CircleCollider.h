#pragma once

#include "physics/Physics.h"

namespace ratchet
{
	class CircleCollider : public Physics
	{
	private:
		//Physics
		float m_radius;
		b2FixtureDef m_fixtureDef;
		b2BodyDef m_bodyDef;
		b2CircleShape m_circleShape;
		b2Body* m_body = nullptr;
		b2Vec2 m_colliderOrigin;

	public:

		//Constructors
		CircleCollider(sf::Sprite& sprite, float radius);
		void initVariables(sf::Sprite& sprite, float radius);

		//Destructors
		~CircleCollider();

		//Getters
		b2BodyDef getBodyDef();
		b2Body* getBody();
		b2CircleShape getColliderShape();
		b2FixtureDef getFixtureDef();

		//Setters
		void setColliderPosition(sf::Sprite& sprite);

		//Checks
	};
}
