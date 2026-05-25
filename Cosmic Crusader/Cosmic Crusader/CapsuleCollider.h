#pragma once

#include "ColliderBase.h"


namespace ratchet
{
	struct CapsuleColliderConfig : public ColliderBaseConfig
	{
		CapsuleColliderConfig();

		std::optional<float> m_radius = std::nullopt;
		std::optional<float> m_height = std::nullopt;
	};

	class CapsuleCollider : public ColliderBase
	{
	public:


		//Constructors
		CapsuleCollider(sf::Sprite& sprite, const CapsuleColliderConfig& cofig);
		void initVariables(sf::Sprite& sprite, const CapsuleColliderConfig& config);

		//Destructors
		~CapsuleCollider() override;

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

		void RestartColliderFeatures(sf::Sprite& sprite, const CapsuleColliderConfig& config);

#ifdef IS_RATCHET_DEBUG
		void printBodyPositionRotation() override;
		void printSpriteColliderPosition(sf::Sprite& sprite, int bodyState) override;
		void debugRender(sf::RenderTarget& target) override;
#endif
		virtual void getMiddlePointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const override;
		bool performGroundRayCast(sf::Sprite& sprite) override;
		bool performSpringRayCast(sf::Sprite& sprite) override;

		virtual void getJumpOverPlatformsBottomRaycastPoints(float& xStart, float& yStart, float& xEnd, float& yEnd, float direction) const override;
		virtual void getJumpOverPlatformsTopRaycastPoints(float& xStart, float& yStart, float& xEnd, float& yEnd, float direction) const override;
		bool performJumpOverPlatformsRaycast(sf::Sprite& sprite, float& direction) override;


		virtual void getCheckFallingRiscRaycastPoints(float& xStart, float& yStart, float& xEnd, float& yEnd, float direction) const override;
		bool performCheckFallingRiskRaycast(sf::Sprite& sprite, float& direction) override;

		float m_height;
		float m_radius;
	private:

		// General

		//Physics
		b2PolygonShape m_boxShape;
		b2CircleShape m_bottomCircleShape;
		b2CircleShape m_topCircleShape;
		b2Vec2 m_offset;
		static int cooliderTypeIndexCount;
	};
}

