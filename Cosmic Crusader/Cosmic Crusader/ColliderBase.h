#pragma once
#include "physics/Physics.h"
namespace ratchet
{
	enum class PhysiscsLayer
	{
		None = 0,
		Platforms,
		Creature, 
		Player,
		Items, 
		Projectiles
	};

	enum ColliderType { COLLIDERTYPE_UNKNOWN = 0, STATIC, DYNAMIC };
	enum ColliderShapeType { COLLIDERSHAPETYPE_UNKNOWN = 0, RECTANGLE, CIRCLE };

	struct BaseColliderConfig
	{
		PhysiscsLayer m_layer;

		b2FixtureDef m_fixtureDef;
		b2BodyDef m_bodyDef;


		BaseColliderConfig();

	};
	class ColliderBase : public Physics
	{
	public:

		//variables
		b2FixtureDef m_fixtureDef;
		b2BodyDef m_bodyDef;
		b2Body* m_body = nullptr;
		b2Vec2 m_colliderOrigin;
		b2Vec2 m_colliderSpriteScale;

		//Constructors
		ColliderBase(const BaseColliderConfig& config);

		virtual void applyMovement(float& movementSpeed, bool& moving, int direction);
		virtual void applyJump(float& jumpSpeed, bool& jumping);

		//Getters
		virtual b2Body* getBody();

		//Prints
		virtual void printBodyPositionRotation();
		virtual void printSpriteColliderPosition(sf::Sprite& sprite, int bodyState);
		virtual void debugRender(sf::RenderTarget& target);

		//Setters
		virtual void setColliderPosition(float x, float y);
		virtual void setColliderRotation(float angle);

		//Checks
		virtual bool performGroundRayCast(sf::Sprite& sprite);

	};

	class GroundCheck : public b2ContactListener
	{
	public:

		bool isPlayerOnGround;
		bool isJumping = false;

		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;
		int colliderTypeIndex;
		std::stringstream ss;
		std::string cooliderIndexText;
		bool isIntersects = false;
		int groundContactCount = 0;
		//bool bottomCollisionDetected = false;

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

