#include "stdafx.h"
#include "RectAngleCollider.h"

RectAngleCollider::RectAngleCollider(sf::Sprite& sprite, int bodyTypeState)
{
	this->InitVariables(sprite, bodyTypeState);
}

void RectAngleCollider::InitVariables(sf::Sprite& sprite, int bodyTypeState)
{
	//Body Def Type
	if (bodyTypeState == DYNAMIC)
	{
		this->bodyDef.type = b2_dynamicBody;
	}
	else if (bodyTypeState == STATIC)
	{
		this->bodyDef.type = b2_staticBody;
	}
	this->bodyDef.position.Set((sprite.getPosition().x + (sprite.getGlobalBounds().width / 2.f)) / metersScale, (sprite.getPosition().y + (sprite.getGlobalBounds().height / 2.f)) / metersScale);
	this->body = this->physicsWorld->CreateBody(&bodyDef);

	//Box Dimensions
	this->boxShape.SetAsBox((sprite.getGlobalBounds().width / 2.0f) / metersScale, (sprite.getGlobalBounds().height / 2.0f) / metersScale);
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

void RectAngleCollider::SetColliderPosition(sf::Sprite& sprite)
{
	this->body->SetTransform(b2Vec2((sprite.getPosition().x + (sprite.getGlobalBounds().width / 2.f)) / metersScale,
		(sprite.getPosition().y + (sprite.getGlobalBounds().height / 2.f)) / metersScale), body->GetAngle());
}


