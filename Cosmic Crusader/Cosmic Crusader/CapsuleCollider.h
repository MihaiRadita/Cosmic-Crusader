#pragma once

#include "ColliderBase.h"


namespace ratchet
{
	struct CapsuleColliderConfig : public BaseColliderConfig
	{
		CapsuleColliderConfig();

		std::optional<float> m_radius = std::nullopt;
		std::optional<float> m_height = std::nullopt;
	};

	class CapsuleCollider : public ColliderBase
	{
	public:

		static GroundCheck* m_contactListener;

		//Constructors
		CapsuleCollider(sf::Sprite& sprite, const CapsuleColliderConfig& cofig);
		void initVariables(sf::Sprite& sprite, const CapsuleColliderConfig& config);

		//Destructors
		~CapsuleCollider();

		//Getters
		float getLocalRadius() const { return m_radius; }
		float getGlobalRadius() const { return m_radius * m_scaleX; }
		float getLocalHeight() const { return m_height; }
		float getGlobalHeight() const { return m_height * m_scaleY; }
		b2BodyDef* getBodyDef();
		b2PolygonShape* getColliderBoxShape();
		b2CircleShape* getBottomColliderCircleShape();
		b2CircleShape* getTopColliderCircleShape();

		b2FixtureDef* getFixtureDef();
		b2Vec2 getOffset();
		b2Vec2 getColliderPosition();
		float getTopCircleRadius();
		float getBottomCircleRadius();

		short userDataName;

#ifdef IS_RATCHET_DEBUG
		void printBodyPositionRotation() override;
		void printSpriteColliderPosition(sf::Sprite& sprite, int bodyState) override;
		void debugRender(sf::RenderTarget& target) override;
#endif
	private:

		// General
		float m_height;
		float m_radius;

		//Physics
		b2PolygonShape m_boxShape;
		b2CircleShape m_bottomCircleShape;
		b2CircleShape m_topCircleShape;
		b2Vec2 m_offset;
		static int cooliderTypeIndexCount;
	};
}

