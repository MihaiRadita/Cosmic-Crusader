#include "stdafx.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(sf::Sprite& sprite, float radius)
{
	this->initVariables(sprite, radius);
}

void CircleCollider::initVariables(sf::Sprite& sprite, float radius)
{
	this->m_radius = radius;

	this->m_bodyDef.type = b2_dynamicBody;
	this->m_bodyDef.position.Set((sprite.getPosition().x + (sprite.getGlobalBounds().width / 2.f)) / sc_metersScale, (sprite.getPosition().y + (sprite.getGlobalBounds().height / 2.f)) / sc_metersScale);
	this->m_body = this->s_physicsWorld->CreateBody(&m_bodyDef);

	//this->circleShape.m_p.Set((sprite.getPosition().x + (sprite.getGlobalBounds().width / 2.f)) / metersScale, (sprite.getPosition().y + (sprite.getGlobalBounds().height / 2.f)) / metersScale);
	this->m_circleShape.m_radius = this->m_radius / sc_metersScale;

	this->m_fixtureDef.shape = &this->m_circleShape;
	this->m_fixtureDef.density = 1.0f;
	this->m_fixtureDef.friction = 0.3f;
	this->m_fixtureDef.restitution = 0.5f;
	m_body->CreateFixture(&this->m_fixtureDef);
}

CircleCollider::~CircleCollider()
{
	if (this->s_physicsWorld)
	{
		if (this->m_body)
		{
			this->s_physicsWorld->DestroyBody(m_body);
			this->m_body = nullptr;
		}
	}
}

b2BodyDef CircleCollider::getBodyDef()
{
	return this->m_bodyDef;
}

b2Body* CircleCollider::getBody()
{
	return this->m_body;
}

b2CircleShape CircleCollider::getColliderShape()
{
	return this->m_circleShape;
}

b2FixtureDef CircleCollider::getFixtureDef()
{
	return this->m_fixtureDef;;
}


void CircleCollider::setColliderPosition(sf::Sprite& sprite)
{
	this->m_body->SetTransform(b2Vec2((sprite.getPosition().x + (sprite.getGlobalBounds().width / 2.f)) / sc_metersScale,
		(sprite.getPosition().y + (sprite.getGlobalBounds().height / 2.f)) / sc_metersScale), m_body->GetAngle());
}
