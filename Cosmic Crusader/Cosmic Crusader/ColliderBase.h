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
		Projectiles
	};

	enum ColliderType { COLLIDERTYPE_UNKNOWN = 0, STATIC, DYNAMIC };

	struct ColliderBaseConfig
	{
		ColliderBaseConfig();
		virtual ~ColliderBaseConfig() = default;

		PhysicsLayer m_layer;

		b2FixtureDef m_fixtureDef;
		b2BodyDef m_bodyDef;

		float m_gravityScale;
		float m_linearDamping;
		float m_angularDamping;

		std::optional<b2Vec2> m_origin = std::nullopt;

#ifdef IS_RATCHET_DEBUG
		bool m_debugDraw = false;
#endif
	};
	class ColliderBase : public Physics
	{
	public:

		//variables
		b2FixtureDef m_fixtureDef;
		b2BodyDef m_bodyDef;
		b2Body* m_body = nullptr;

		bool m_skipRaycastThisFrame = false;


		//Constructors
		ColliderBase(const ColliderBaseConfig& config);
		~ColliderBase();

		void applyMovement(const bool& changeX, const float& xVelocity, const bool& changeY, const float& yVelocity);

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

		//Checks
		virtual void getLeftPointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const;
		virtual void getMiddlePointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const;
		virtual void getRightPointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const;
		virtual bool performGroundRayCast(sf::Sprite& sprite);

	protected:
		b2Vec2 m_origin;
		float m_scaleX = 1.0f;
		float m_scaleY = 1.0f;

#ifdef IS_RATCHET_DEBUG
		bool m_debugDraw = false;
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

}

