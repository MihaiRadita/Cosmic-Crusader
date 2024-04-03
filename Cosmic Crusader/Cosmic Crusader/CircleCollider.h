#pragma once
class CircleCollider
{
private:
	sf::CircleShape circleCollider;
	float radius;
	sf::Vector2f circlePosition;
	sf::Vector2f circleScale;
public:

	//Constructors
	CircleCollider(float& radius, float& xPosition, float& yPosition, float& xScale, float& yScale);

	//Destructors
	~CircleCollider();

	//Getters
	float GetRadius();
	sf::CircleShape GetCircleCollider();

	//Setters
	void SetCircleRadius(float& radius);

	//Checks
	bool CheckCollsion(sf::CircleShape& colliderCheck);
};

