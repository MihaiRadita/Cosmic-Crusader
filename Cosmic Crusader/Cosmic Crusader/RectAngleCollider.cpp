#include "stdafx.h"
#include "RectAngleCollider.h"

RectAngleCollider::RectAngleCollider(float& positionX, float& positionY,float& scaleX, float& scaleY)
{
	this->xPosition = positionX;
	this->yPosition = positionY;
	this->xScale = scaleX;
	this->yScale = scaleY;

	this->rectAngleCollider.setPosition(this->xPosition, this->yPosition);
	this->rectAngleCollider.setScale(this->xScale, this->yScale);
}

RectAngleCollider::~RectAngleCollider()
{
}

sf::RectangleShape RectAngleCollider::GetColliderShape()
{
	return this->rectAngleCollider;
}

sf::Vector2f RectAngleCollider::GetColliderPosition()
{
	return this->rectAngleCollider.getPosition();
}

sf::Vector2f RectAngleCollider::GetColliderScale()
{
	return this->rectAngleCollider.getScale();
}

bool RectAngleCollider::CheckRectAngleCollision(sf::RectangleShape& coliderChecking)
{
	if (this->CheckSegment1(coliderChecking) || this->CheckSegment2(coliderChecking))
	{
		return true;
	}

	return false;
}

bool RectAngleCollider::CheckSegment1(sf::RectangleShape& colliderCheking)
{
	if (((this->rectAngleCollider.getGlobalBounds().left >= colliderCheking.getGlobalBounds().left &&
		this->rectAngleCollider.getGlobalBounds().left <= colliderCheking.getGlobalBounds().left + colliderCheking.getGlobalBounds().width) &&
		(this->rectAngleCollider.getGlobalBounds().top >= colliderCheking.getGlobalBounds().top &&
		this->rectAngleCollider.getGlobalBounds().top <= colliderCheking.getGlobalBounds().top + colliderCheking.getGlobalBounds().height)) ||
		((this->rectAngleCollider.getGlobalBounds().left + this->rectAngleCollider.getGlobalBounds().width >= colliderCheking.getGlobalBounds().left &&
		  this->rectAngleCollider.getGlobalBounds().left + this->rectAngleCollider.getGlobalBounds().width <= colliderCheking.getGlobalBounds().left + colliderCheking.getGlobalBounds().width) &&
		 (this->rectAngleCollider.getGlobalBounds().top >= colliderCheking.getGlobalBounds().top &&
		  this->rectAngleCollider.getGlobalBounds().top <= colliderCheking.getGlobalBounds().top + colliderCheking.getGlobalBounds().height)))
	{
		return true;
	}
	return false;
}

bool RectAngleCollider::CheckSegment2(sf::RectangleShape& coliderChecking)
{
	if (((this->rectAngleCollider.getGlobalBounds().left + this->rectAngleCollider.getGlobalBounds().width >= coliderChecking.getGlobalBounds().left &&
		this->rectAngleCollider.getGlobalBounds().left + this->rectAngleCollider.getGlobalBounds().width <= coliderChecking.getGlobalBounds().left + coliderChecking.getGlobalBounds().width) &&
		(this->rectAngleCollider.getGlobalBounds().top + this->rectAngleCollider.getGlobalBounds().height >= coliderChecking.getGlobalBounds().top &&
		this->rectAngleCollider.getGlobalBounds().top + this->rectAngleCollider.getGlobalBounds().height <= coliderChecking.getGlobalBounds().top + coliderChecking.getGlobalBounds().height)) ||
		((this->rectAngleCollider.getGlobalBounds().left >= coliderChecking.getGlobalBounds().left &&
		this->rectAngleCollider.getGlobalBounds().left <= coliderChecking.getGlobalBounds().left + coliderChecking.getGlobalBounds().width) &&
		(this->rectAngleCollider.getGlobalBounds().top + this->rectAngleCollider.getGlobalBounds().height >= coliderChecking.getGlobalBounds().top &&
		this->rectAngleCollider.getGlobalBounds().top + this->rectAngleCollider.getGlobalBounds().height <= coliderChecking.getGlobalBounds().top + coliderChecking.getGlobalBounds().height)))
	{
		return true;
	}
		
	return false;
}
