#pragma once
#include "physics/Physics.h"
#include "physics/ContactListener.h"

namespace ratchet
{
	enum class PhysicsLayer
	{
		None = 0,
		Platforms,
		Creature, 
		Player,
		Items, 
		Projectiles,
		CheckPoints,
		DeathFallTrigger
	};

	enum ColliderType { COLLIDERTYPE_UNKNOWN = 0, STATIC, DYNAMIC };

	struct ColliderBaseConfig
	{
		ColliderBaseConfig();
		virtual ~ColliderBaseConfig() = default;

		PhysicsLayer m_layer;

		b2FixtureDef m_fixtureDef;
		b2BodyDef m_bodyDef;
		b2MassData m_massData;

		float m_massValue = 0.f;

		float m_gravityScale;
		float m_linearDamping;
		float m_angularDamping;

		float m_collierFacingDirectionX;
		float m_colliderFacingDirectionY;

		float m_JumpOverBottomRaycastOffsetX;
		float m_JumpOverBottomRaycastOffsetY;

		float m_JumpOverTopRaycastOffsetX;
		float m_JumpOverTopRaycastOffsetY;

		float m_isGroundRaycastOffset;

		float m_checkFallingRiskRaycastStartOffsetX;
		float m_checkFallingRiskRaycastStartOffsetY;

		float m_checkFallingRiskRaycastEndOffsetX;
		float m_checkFallingRiskRaycastEndOffsetY;

		std::optional<b2Vec2> m_origin = std::nullopt;


#ifdef IS_RATCHET_DEBUG
		bool m_debugDraw = false;
#endif
	};

	class GameObject;

	class ColliderBase : public Physics
	{
	public:

		//variables
		b2FixtureDef m_fixtureDef;
		b2BodyDef m_bodyDef;
		b2Body* m_body = nullptr;
		b2MassData m_massData;

		PhysicsLayer m_layer;

		bool m_isColliderSetDestroy = false;

		float m_massValue = 0.f;

		bool m_skipRaycastThisFrame = false;

		float m_collierFacingDirectionX;
		float m_colliderFacingDirectionY;

		float m_JumpOverBottomRaycastOffsetX;
		float m_JumpOverBottomRaycastOffsetY;

		float m_JumpOverTopRaycastOffsetX;
		float m_JumpOverTopRaycastOffsetY;

		float m_isGroundRaycastOffset;

		float m_checkFallingRiskRaycastStartOffsetX;
		float m_checkFallingRiskRaycastStartOffsetY;

		float m_checkFallingRiskRaycastEndOffsetX;
		float m_checkFallingRiskRaycastEndOffsetY;


		float m_checkTopPlatformsDirectionX;

		bool isColliderToDestroy();

		short m_userDataName;
		GameObject* m_obj;


		//Constructors
		ColliderBase(const ColliderBaseConfig& config);
		virtual ~ColliderBase() = default;

		void applyMovement(const bool& changeX, const float& xVelocity, const bool& changeY, const float& yVelocity);

		void SetOwner(GameObject* obj);

		//Getters
		virtual b2Body* getBody();
		b2Vec2 getColliderOrigin() const;

		//Prints
#ifdef IS_RATCHET_DEBUG
		virtual void printBodyPositionRotation();
		virtual void printSpriteColliderPosition(sf::Sprite& sprite, int bodyState);
		virtual void debugRender(sf::RenderTarget& target);
#endif
		virtual void drawColliderCenterBased(sf::RenderTarget& target);

		//Setters
		virtual void setColliderPosition(float x, float y);
		virtual void setColliderRotation(float angle);
		virtual void setColliderOrigin(b2Vec2 origin) { m_origin = origin; }

		//Checks for Ground
		virtual void getLeftPointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const;
		virtual void getMiddlePointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const;
		virtual void getRightPointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const;
		virtual bool performGroundRayCast(sf::Sprite& sprite);
		virtual bool performUpPlatformRayCast(sf::Sprite& sprite);

		//Checks for Jump Over Platforms
		virtual void getJumpOverPlatformsBottomRaycastPoints(float& xStart, float& yStart, float& xEnd, float& yEnd, float direction) const;
		virtual void getJumpOverPlatformsTopRaycastPoints(float& xStart, float& yStart, float& xEnd, float& yEnd, float direction) const;
		virtual bool performJumpOverPlatformsRaycast(sf::Sprite& sprite, float& direction);

		//Checks for Follow Target

		virtual void getCheckFollowTargetRaycastPoints(float& xStart, float& yStart, float& xEnd, float& yEnd, float direction);
		virtual bool performFollowTargetRayCast(const sf::Vector2f& charaterPosition, const sf::Vector2f& targetPosition);

		//Check Falling Risk
		virtual void getCheckFallingRiscRaycastPoints(float& xStart, float& yStart, float& xEnd, float& yEnd, float direction) const;
		virtual bool performCheckFallingRiskRaycast(sf::Sprite& sprite, float& direction);

	protected:
		b2Vec2 m_origin;
		float m_scaleX = 1.0f;
		float m_scaleY = 1.0f;

#ifdef IS_RATCHET_DEBUG
		bool m_debugDraw = true;
#endif
	};

	class GroundCheck
	{
	public:

		bool isPlayerOnGround;
		bool isJumping = false;

		/*void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;*/

		int colliderTypeIndex;
		std::stringstream ss;
		std::string cooliderIndexText;
		bool isIntersects = false;
		int groundContactCount = 0;

		std::string getCollisionSide(const b2Vec2& localPoint, const b2AABB& aabb);

		bool CompareCharacters(std::string& name, std::string name2);
	};

	class GroundRayCastCallBack : public b2RayCastCallback
	{

	public:
		GroundRayCastCallBack(b2Body* ingnoedBody);

		float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override;

		bool m_hit;
		b2Vec2 m_point;
		b2Vec2 m_normal;
		float m_fraction;
		b2Body* m_ignoredBody;

	};

	class JumpOverPlatformsRayCastCallBack : public b2RayCastCallback
	{
	public:

		JumpOverPlatformsRayCastCallBack(b2Body* ingonerdBody);

		float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override;

		bool m_hit;
		b2Vec2 m_point;
		b2Vec2 m_normal;
		float m_fraction;
		b2Body* m_ignoredBody;
	};

	class CheckFallingRiskRaycastCallBack : public b2RayCastCallback
	{
	public:

		CheckFallingRiskRaycastCallBack(b2Body* ignoredBody);

		float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override;

		bool m_hit;
		b2Vec2 m_point;
		b2Vec2 m_normal;
		float m_fraction;
		b2Body* m_ignoredBody;
	};

	class CheckFollowTargetRaycastCallBack : public b2RayCastCallback
	{
	public:
		CheckFollowTargetRaycastCallBack(b2Body* ignoredBody);

		float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override;

		bool m_hit;
		b2Vec2 m_point;
		b2Vec2 m_normal;
		float m_fraction;
		b2Body* m_ignoredBody;
	};

}

