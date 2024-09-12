#pragma once

#include "ColliderBase.h"

namespace ratchet
{
	struct RectAngleColliderConfig : public BaseColliderConfig
	{
		b2Vec2 m_colliderOffset;


		RectAngleColliderConfig();
	};

	class RectAngleCollider : public ColliderBase
	{
	private:

		//Physics
		b2PolygonShape m_boxShape;
		b2Vec2 m_offset;
		b2Vec2 m_vs[4];
		static int cooliderTypeIndexCount;


	public:

		static GroundCheck* m_contactListener;

		//Constructors
		RectAngleCollider(sf::Sprite& sprite, const RectAngleColliderConfig& congif);
		void initVariables(sf::Sprite& sprite, const RectAngleColliderConfig& config);

		//Destructors
		~RectAngleCollider();

		//Getters
		b2BodyDef* getBodyDef();
		b2Body* getBody() override;
		b2PolygonShape* getColliderShape();
		b2FixtureDef* getFixtureDef();
		b2Vec2 getOffset();
		b2Vec2* getColliderScale();
		b2Vec2 getColliderPosition();
		short userDataName;


		//Setters
		void setColliderPosition(float x, float y) override;
		void setColliderRotation(float angle) override;

		//Checks
#ifdef IS_RATCHET_DEBUG
		void printBodyPositionRotation() override;
		void printSpriteColliderPosition(sf::Sprite& sprite, int bodyState) override;
		void debugRender(sf::RenderTarget& target) override;
#endif
		void applyMovement(float& movementSpeed, bool& moving, int direction) override;
		void applyJump(float& jumpSpeed, bool& jumping) override;

		//Checks
		bool performGroundRayCast(sf::Sprite& sprite) override;
	};
}