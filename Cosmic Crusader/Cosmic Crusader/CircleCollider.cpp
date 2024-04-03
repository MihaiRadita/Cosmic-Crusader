#include "stdafx.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(float& radius, float& xPosition, float& yPostion, float& xScale, float& yScale)
{
	this->radius = radius;
	this->SetCircleRadius(this->radius);
	this->circlePosition.x = xPosition;
	this->circlePosition.y = yPostion;
	this->circleScale.x = this->circleCollider.getRadius() * 2;
	this->circleScale.y = this->circleCollider.getRadius() * 2;
	this->circleCollider.setPosition(this->circlePosition);
	this->circleCollider.setScale(this->circleScale);
}

CircleCollider::~CircleCollider()
{
}

float CircleCollider::GetRadius()
{
	return this->circleCollider.getRadius();
}

sf::CircleShape CircleCollider::GetCircleCollider()
{
	return this->circleCollider;
}

void CircleCollider::SetCircleRadius(float& radius)
{
	this->circleCollider.setRadius(radius);
}

bool CircleCollider::CheckCollsion(sf::CircleShape& colliderCheck)
{
	/*float xDisance = this->circleCollider.getPosition().x - colliderCheck.getPosition().x;
	float yDistance = this->circleCollider.getPosition().y - colliderCheck.getPosition().y;*/
	
	sf::Vector2f distance = this->circleCollider.getPosition() - colliderCheck.getPosition();
	float radiusSum = this->circleCollider.getRadius() + colliderCheck.getRadius();

	if (distance.x <= radiusSum && distance.y <= radiusSum)
	{
		return true;
	}
	

	return false;
}
