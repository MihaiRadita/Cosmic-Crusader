#pragma once

#include "ColliderBase.h"

namespace ratchet
{
	struct CircleColliderConfig : public ColliderBaseConfig
	{
		std::optional<float> m_radius = std::nullopt;

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
		b2Vec2 m_origin;

		short m_userDataName;
		b2CircleShape m_shape;

	public:

		//Constructors
		CircleCollider(sf::Sprite& sprite, const CircleColliderConfig& config);
		void initVariables(sf::Sprite& sprite, const CircleColliderConfig& config);

		void drawColliderCenterBased(sf::RenderTarget& target) override;

		//Destructors
		~CircleCollider();

		//Getters
		b2BodyDef getBodyDef();
		b2Body* getBody();
		b2CircleShape getColliderShape();
		b2FixtureDef getFixtureDef();
		float getLocalRadius() const { return m_radius; }
		float getGlobalRadius() const { return m_radius * m_scaleX; }

		//Setters
		void setColliderPosition(sf::Sprite& sprite);

		//Checks
	};
}
