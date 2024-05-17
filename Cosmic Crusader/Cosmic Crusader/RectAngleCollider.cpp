#include "stdafx.h"
#include "RectAngleCollider.h"

RectAngleCollider::RectAngleCollider(sf::Sprite& sprite, int bodyTypeState)
{
	this->InitVariables(sprite, bodyTypeState);
}

void RectAngleCollider::InitVariables(sf::Sprite& sprite, int bodyTypeState)
{
	//Body Def Type

	this->colliderSpritePosition = b2Vec2((sprite.getPosition().x + (sprite.getLocalBounds().width / (2.0f * 10))),
		(sprite.getPosition().y + (sprite.getLocalBounds().height / (2.0f * 10))));

	this->colliderSpriteScale = b2Vec2((sprite.getLocalBounds().width / 2.0f) , (sprite.getLocalBounds().height / 2.0f));

	if (bodyTypeState == DYNAMIC)
	{
		this->bodyDef.type = b2_dynamicBody;
	}
	else if (bodyTypeState == STATIC)
	{
		this->bodyDef.type = b2_staticBody;
	}
	//this->bodyDef.position.Set((sprite.getPosition().x + (sprite.getGlobalBounds().width / 2.f)), (sprite.getPosition().y + (sprite.getGlobalBounds().height / 2.f)));
	this->bodyDef.position.Set(this->colliderSpritePosition.x, this->colliderSpritePosition.y);
	this->bodyDef.fixedRotation = true;
	this->body = this->physicsWorld->CreateBody(&bodyDef);

	//Box Dimensions
	this->boxShape.SetAsBox(this->colliderSpriteScale.x, this->colliderSpriteScale.y);
	//Box fixtures properties
	this->fixtureDef.shape = &this->boxShape;
	if (bodyTypeState == DYNAMIC)
	{
		this->fixtureDef.density = 1.0f;
		this->fixtureDef.friction = 0.3f;
		this->fixtureDef.restitution = 0.5f;
	}
	else if (bodyTypeState == STATIC)
	{
		this->fixtureDef.density = 0.f;
		this->fixtureDef.friction = 0.f;
		this->fixtureDef.restitution = 0.f;
	}
	this->body->CreateFixture(&this->fixtureDef);

	if (bodyTypeState == STATIC)
	{
		std::cout << "Static position is " << this->colliderSpritePosition.x << " , " << this->colliderSpritePosition.y << " VS Sprite position " <<
											sprite.getPosition().x << " , " << sprite.getPosition().y << std::endl;
	}
	else if (bodyTypeState == DYNAMIC)
	{
		std::cout << "Dynamic position is " << this->colliderSpritePosition.x << " , " << this->colliderSpritePosition.y << " VS Sprite position " <<
											sprite.getPosition().x << " , " << sprite.getPosition().y << std::endl;
	}
}

RectAngleCollider::~RectAngleCollider()
{
	if (this->physicsWorld)
	{
		if (this->body)
		{
			this->physicsWorld->DestroyBody(body);
			this->body = nullptr;
		}
	}
}

b2BodyDef RectAngleCollider::GetBodyDef()
{
	return this->bodyDef;
}

b2Body* RectAngleCollider::GetBody()
{
	return this->body;
}

b2PolygonShape RectAngleCollider::GetColliderShape()
{
	return this->boxShape;
}

b2FixtureDef RectAngleCollider::GetFixtureDef()
{
	return this->fixtureDef;;
}

b2Vec2* RectAngleCollider::GetColliderScale()
{
	return &this->colliderSpriteScale;
}

b2Vec2* RectAngleCollider::GetColliderPosition()
{
	return &this->colliderSpritePosition;
}

void RectAngleCollider::SetColliderPosition(sf::Sprite& sprite)
{
	this->body->SetTransform(b2Vec2((sprite.getPosition().x + (sprite.getLocalBounds().width / 2.f)) / 32.f,
		(sprite.getPosition().y + (sprite.getLocalBounds().height / 2.f))), this->body->GetAngle());
}

void RectAngleCollider::PrintBodyPositionRotation()
{
	std::cout << this->body->GetPosition().x << " x axis " << this->body->GetPosition().y<<" y axis " << std::endl;
	std::cout << this->body->GetAngle()<<" degrees " << std::endl;
}

void RectAngleCollider::SetColliderBySprite(sf::Sprite& sprite)
{
	this->bodyDef.position.Set((sprite.getPosition().x + (sprite.getGlobalBounds().width / 2.f)), (sprite.getPosition().y + (sprite.getGlobalBounds().height / 2.f)));
}

void RectAngleCollider::PrintSpriteColliderPosition(sf::Sprite& sprite, int bodyState)
{
	if (bodyState == STATIC)
	{
		std::cout << "Static position is " << this->colliderSpritePosition.x << " , " << this->colliderSpritePosition.y << " VS Sprite position " <<
			sprite.getPosition().x << " , " << sprite.getPosition().y << std::endl;
	}
	else if (bodyState == DYNAMIC)
	{
		std::cout << "Dynamic position is " << this->colliderSpritePosition.x << " , " << this->colliderSpritePosition.y << " VS Sprite position " <<
											sprite.getPosition().x << " , " << sprite.getPosition().y << std::endl;
	}
}


