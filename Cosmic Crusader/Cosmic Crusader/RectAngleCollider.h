#pragma once

#include "Physics.h"


class RectAngleCollider : public Physics
{
private:

	//Physics
	b2PolygonShape boxShape;
	b2FixtureDef fixtureDef;
	b2BodyDef bodyDef;
	b2Body* body = nullptr;
	b2Vec2 colliderOrigin;
	b2Vec2 colliderSpritePosition;
	b2Vec2 colliderSpriteScale;
	int bodyTypeState;
	b2Vec2 vs[4];
	b2EdgeShape boxShape1;


public:
	//Constructors
	RectAngleCollider(sf::Sprite& sprite, int bodyTypeState);
	void InitVariables(sf::Sprite& sprite, int bodyTypeState);

	//Destructors
	~RectAngleCollider();

	//Getters
	b2BodyDef GetBodyDef();
	b2Body* GetBody();
	b2PolygonShape GetColliderShape();
	b2FixtureDef GetFixtureDef();
	
	b2Vec2* GetColliderScale();
	b2Vec2* GetColliderPosition();


	//Setters
	void SetColliderPosition(sf::Sprite& sprite);

	//Checks

	void PrintBodyPositionRotation();
	
	void SetColliderBySprite(sf::Sprite& sprite);

	void PrintSpriteColliderPosition(sf::Sprite& sprite, int bodyState);
};

