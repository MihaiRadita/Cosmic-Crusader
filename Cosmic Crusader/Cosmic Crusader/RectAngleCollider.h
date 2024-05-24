#pragma once

#include "Physics.h"

enum EntityType {
	PLAYER,
	TILE
};
//
struct UserData {
	EntityType type;
};
class GroundCheck : public b2ContactListener
{
public:

	bool isPlayerOnGround;

	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
};

class RectAngleCollider : public Physics
{
private:

	//Physics
	b2PolygonShape m_boxShape;
	b2FixtureDef m_fixtureDef;
	b2BodyDef m_bodyDef;
	b2Body* m_body = nullptr;
	b2Vec2 m_colliderOrigin;
	b2Vec2 m_colliderSpriteScale;
	b2Vec2 m_offset;
	int m_bodyTypeState;
	b2Vec2 m_vs[4];
	b2EdgeShape m_boxShape1;
	bool m_isGround = false;


public:
	//static std::vector<sf::Texture>* s_animFrameImg;
	static GroundCheck* m_contactListener;
	//Constructors
	RectAngleCollider(sf::Sprite& sprite, int bodyTypeState);
	void initVariables(sf::Sprite& sprite, int bodyTypeState);

	//Destructors
	~RectAngleCollider();

	//Getters
	b2BodyDef* getBodyDef();
	b2Body* getBody();
	b2PolygonShape* getColliderShape();
	b2FixtureDef* getFixtureDef();
	b2Vec2 getOffset();
	b2Vec2* getColliderScale();
	b2Vec2 getColliderPosition();


	//Setters
	void setColliderPosition(float x, float y);

	//Checks
	void printBodyPositionRotation();
	void printSpriteColliderPosition(sf::Sprite& sprite, int bodyState);
	void debugRender(sf::RenderTarget& target);
	void applyMovement(float& movementSpeed, bool& moving, int direction);
	void applyJump(float& jumpSpeed, bool& jumping);
};

