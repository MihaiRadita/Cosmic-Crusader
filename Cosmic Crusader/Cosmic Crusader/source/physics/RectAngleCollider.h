#pragma once

#include "ColliderBase.h"

namespace ratchet
{
	struct RectAngleColliderConfig : public ColliderBaseConfig
	{
		RectAngleColliderConfig();

		RectAngleColliderConfig(const RectAngleColliderConfig& other)
			: ColliderBaseConfig(other), 
			m_width(other.m_width),
			m_height(other.m_height)
		{

		}

		std::optional<float> m_width = std::nullopt;
		std::optional<float> m_height = std::nullopt;
	};

	class RectAngleCollider : public ColliderBase
	{
	public:


		//Constructors
		RectAngleCollider(sf::Sprite& sprite, const RectAngleColliderConfig& congif);
		void initVariables(sf::Sprite& sprite, const RectAngleColliderConfig& config);

		//Destructors
		~RectAngleCollider() override;

		//Getters
		float getLocalWidth() const { return m_width; }
		float getGlobalWidth() const { return m_width * m_scaleX; }
		float getLocalHeight() const { return m_height; } 
		float getGlobalHeight() const { return m_height * m_scaleY; } 
		b2BodyDef* getBodyDef();
		b2PolygonShape* getColliderShape();
		b2FixtureDef* getFixtureDef();
		b2Vec2 getOffset();
		b2Vec2 getColliderPosition();

		//Checks
#ifdef IS_RATCHET_DEBUG
		void printBodyPositionRotation() override;
		void printSpriteColliderPosition(sf::Sprite& sprite, int bodyState) override;
		void debugRender(sf::RenderTarget& target) override;
#endif

		void drawColliderCenterBased(sf::RenderTarget& target) override;

		//Checks
		virtual void getLeftPointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const override;
		virtual void getMiddlePointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const override;
		virtual void getRightPointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const override;
		bool performGroundRayCast(sf::Sprite& sprite) override;

	private:

		// General
		float m_width;
		float m_height;
		b2PolygonShape m_boxShape;

		//Physics
		b2Vec2 m_offset;
		b2Vec2 m_vs[4];
		static int cooliderTypeIndexCount;
	};
}