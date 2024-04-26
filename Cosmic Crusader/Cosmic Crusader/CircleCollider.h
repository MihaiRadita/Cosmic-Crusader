#pragma once

#include "Physics.h"

class CircleCollider: public Physics 
{
private:
	//Physics
	float radius;
	b2FixtureDef fixtureDef;
	b2BodyDef bodyDef;
	b2CircleShape circleShape;
	b2Body* body = nullptr;
	b2Vec2 colliderOrigin;

public:

	//Constructors
	CircleCollider(sf::Sprite& sprite, float radius);
	void InitVariables(sf::Sprite& sprite, float radius);

	//Destructors
	~CircleCollider();

	//Getters
	float GetRadius();
	b2BodyDef GetBodyDef();
	b2Body* GetBody();
	b2CircleShape GetColliderShape();
	b2FixtureDef GetFixtureDef();

	//Setters
	void SetColliderPosition(sf::Sprite& sprite);

	//Checks
};

