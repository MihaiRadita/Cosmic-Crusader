#pragma once

#include "Physics.h"


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
public:
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
};

