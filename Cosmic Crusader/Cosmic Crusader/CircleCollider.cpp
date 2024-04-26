#include "stdafx.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(sf::Sprite& sprite, float radius)
{
	this->InitVariables(sprite, radius);
}

void CircleCollider::InitVariables(sf::Sprite& sprite, float radius)
{
	this->radius = radius;

	this->bodyDef.type = b2_dynamicBody;
	this->bodyDef.position.Set((sprite.getPosition().x + (sprite.getGlobalBounds().width / 2.f)) / metersScale, (sprite.getPosition().y + (sprite.getGlobalBounds().height / 2.f)) / metersScale);
	this->body = this->physicsWorld->CreateBody(&bodyDef);

	//this->circleShape.m_p.Set((sprite.getPosition().x + (sprite.getGlobalBounds().width / 2.f)) / metersScale, (sprite.getPosition().y + (sprite.getGlobalBounds().height / 2.f)) / metersScale);
	this->circleShape.m_radius = this->radius / metersScale;

	this->fixtureDef.shape = &this->circleShape;
	this->fixtureDef.density = 1.0f;
	this->fixtureDef.friction = 0.3f;
	this->fixtureDef.restitution = 0.5f;
	body->CreateFixture(&this->fixtureDef);
}

CircleCollider::~CircleCollider()
{
	this->body->GetWorld()->DestroyBody(body);
	this->body = nullptr;
}

b2BodyDef CircleCollider::GetBodyDef()
{
	return this->bodyDef;
}

b2Body* CircleCollider::GetBody()
{
	return this->body;
}

b2CircleShape CircleCollider::GetColliderShape()
{
	return this->circleShape;
}

b2FixtureDef CircleCollider::GetFixtureDef()
{
	return this->fixtureDef;;
}


void CircleCollider::SetColliderPosition(sf::Sprite& sprite)
{
	this->body->SetTransform(b2Vec2((sprite.getPosition().x + (sprite.getGlobalBounds().width / 2.f)) / metersScale,
		(sprite.getPosition().y + (sprite.getGlobalBounds().height / 2.f)) / metersScale), body->GetAngle());
}
