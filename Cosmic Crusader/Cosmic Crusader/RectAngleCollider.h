#pragma once

#include "Physics.h"

class RectAngleCollider : public Physics
{
private:
	sf::RectangleShape rectAngleCollider;
	sf::Vector2f colliderPosition;
	sf::Vector2f colliderScale;
	float xPosition;
	float yPosition;
	float xScale;
	float yScale;

	//Physics
	b2PolygonShape boxShape;
	b2FixtureDef fixtureDef;
	b2BodyDef bodyDef;
	b2Body* body = nullptr;
	b2Vec2 colliderOrigin;

public:
	//Constructors
	RectAngleCollider(sf::Sprite& sprite);
	void InitVariables();

	//Destructors
	~RectAngleCollider();

	//Getters
	sf::RectangleShape GetColliderShape();
	sf::Vector2f GetColliderPosition();
	sf::Vector2f GetColliderScale();
	
	//Checks
	bool CheckRectAngleCollision(sf::RectangleShape& coliderChecking);
	bool CheckSegment1(sf::RectangleShape& colliderCheking);
	bool CheckSegment2(sf::RectangleShape& coliderChecking);


	//Setters
};

