#pragma once

#include "ColliderBase.h"

namespace ratchet
{
	struct CircleColliderConfig : public BaseColliderConfig
	{
		float radiusOffset;

		CircleColliderConfig();
	};

	class CircleCollider : public ColliderBase
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
		CircleCollider(sf::Sprite& sprite, const CircleColliderConfig& config);
		void initVariables(sf::Sprite& sprite, const CircleColliderConfig& config);

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
