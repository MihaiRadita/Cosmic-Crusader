#pragma once
class RectAngleCollider
{
private:
	sf::RectangleShape rectAngleCollider;
	sf::Vector2f colliderPosition;
	sf::Vector2f colliderScale;
	float xPosition;
	float yPosition;
	float xScale;
	float yScale;

public:
	//Constructors
	RectAngleCollider(float& xPosition, float& yPosition,float& xScale, float& yScale);

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

