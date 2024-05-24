#include "stdafx.h"
#include "RectAngleCollider.h"

//Listeners

void GroundCheck::BeginContact(b2Contact* contact)
{
	uintptr_t fixtureUserDataA = contact->GetFixtureA()->GetUserData().pointer;
	uintptr_t fixtureUserDataB = contact->GetFixtureB()->GetUserData().pointer;

	if (fixtureUserDataA && fixtureUserDataB) {
		UserData* dataA = reinterpret_cast<UserData*>(fixtureUserDataA);
		UserData* dataB = reinterpret_cast<UserData*>(fixtureUserDataB);

		if ((dataA->type == PLAYER && dataB->type == TILE) ||
			(dataA->type == TILE && dataB->type == PLAYER)) {

			b2WorldManifold worldManifold;
			contact->GetWorldManifold(&worldManifold);

			for (int i = 0; i < contact->GetManifold()->pointCount; ++i) {
				b2Vec2 point = worldManifold.points[i];

				if (dataA->type == PLAYER && dataB->type == TILE) {
					float playerBottom = contact->GetFixtureA()->GetAABB(0).lowerBound.y;
					float tileTop = contact->GetFixtureB()->GetAABB(0).upperBound.y;
					if (point.y <= playerBottom && point.y >= tileTop) {
						isPlayerOnGround = true;
						std::cout << std::endl;
						std::cout << std::endl;
						std::cout << "Player ISGROUND = " << isPlayerOnGround << std::endl << std::endl;
						return; // Opriti cautarea mai departe
					}
				}
				else if (dataA->type == TILE && dataB->type == PLAYER) {
					float playerBottom = contact->GetFixtureB()->GetAABB(0).lowerBound.y;
					float tileTop = contact->GetFixtureA()->GetAABB(0).upperBound.y;
					if (point.y <= playerBottom && point.y >= tileTop) {
						isPlayerOnGround = true;
						std::cout << std::endl;
						std::cout << std::endl;
						std::cout << "Player ISGROUND = " << isPlayerOnGround << std::endl << std::endl;
						return; // Opriti cautarea mai departe
					}
				}
			}
		}
	}
}

void GroundCheck::EndContact(b2Contact* contact)
{
	uintptr_t bodyUserDataA = contact->GetFixtureA()->GetUserData().pointer;
	uintptr_t bodyUserDataB = contact->GetFixtureB()->GetUserData().pointer;

	if (bodyUserDataA && bodyUserDataB) {
		UserData* dataA = reinterpret_cast<UserData*>(bodyUserDataA);
		UserData* dataB = reinterpret_cast<UserData*>(bodyUserDataB);

		if ((dataA->type == PLAYER && dataB->type == TILE) ||
			(dataA->type == TILE && dataB->type == PLAYER)) {
			GroundCheck::isPlayerOnGround = false;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "Player ISGROUND = " << isPlayerOnGround << std::endl << std::endl;
		}
	}
}

RectAngleCollider::RectAngleCollider(sf::Sprite& sprite, int bodyTypeState)
{
	initVariables(sprite, bodyTypeState);
}

void RectAngleCollider::initVariables(sf::Sprite& sprite, int bodyTypeState)
{
	//Body Def Type
	m_offset = b2Vec2(20.0f, 0.0f);

	if (!m_contactListener)
	{
		m_contactListener = new GroundCheck();
		s_physicsWorld->SetContactListener(m_contactListener);
	}
	//m_colliderOrigin = b2Vec2(sprite.getOrigin().x / 2.0f, sprite.getOrigin().y / 2.0f);
	m_colliderOrigin = b2Vec2(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	m_colliderSpriteScale = b2Vec2(
		sprite.getGlobalBounds().width, 
		sprite.getLocalBounds().height
	);

	if (bodyTypeState == DYNAMIC)
	{
		m_bodyDef.type = b2_dynamicBody;
		m_bodyDef.bullet = true;
	}
	else if (bodyTypeState == STATIC)
	{
		m_bodyDef.type = b2_staticBody;
	
	}


	m_bodyDef.position.Set(sprite.getPosition().x + this->m_colliderSpriteScale.x / 2.0f, sprite.getPosition().y + this->m_colliderSpriteScale.y / 2.0f);
	m_bodyDef.fixedRotation = true;
	m_body = s_physicsWorld->CreateBody(&m_bodyDef);
	

	//Box Dimensions
	m_boxShape.SetAsBox(m_colliderSpriteScale.x / 2.0f, m_colliderSpriteScale.y / 2.0f,m_colliderOrigin, this->m_body->GetAngle());
	//Box fixtures properties
	m_fixtureDef.shape = &m_boxShape;
	if (bodyTypeState == DYNAMIC)
	{
		m_fixtureDef.density = 1.0f;
		m_fixtureDef.friction = 0.3f;
		m_fixtureDef.restitution = 0.5f;
	}
	else if (bodyTypeState == STATIC)
	{
		m_fixtureDef.density = 0.f;
		m_fixtureDef.friction = 0.3f;
		m_fixtureDef.restitution = 0.f;
	}
	m_fixtureDef.userData.pointer = (uintptr_t)this;

	m_body->CreateFixture(&m_fixtureDef);

	if (bodyTypeState == STATIC)
	{
		std::cout << std::endl;
		std::cout << "Static Sprite position is " << sprite.getPosition().x << " , " << sprite.getPosition().y << std::endl;
		std::cout << "Static Sprite scale is " << sprite.getScale().x << " , " << sprite.getScale().y << std::endl;

		b2Vec2 origin = m_body->GetLocalCenter();
		b2Vec2 position = m_body->GetTransform().p;
		float rotaion = m_body->GetAngle();

		std::cout << "Static Collider origin " << origin.x << " , " << origin.y << std::endl;
		std::cout << "Static Collider position " << position.x << " , " << position.y << std::endl;
		std::cout << "Static Collider roatation " << rotaion << std::endl;

		std::cout << std::endl;

	}
	else if (bodyTypeState == DYNAMIC)
	{
		std::cout << std::endl;
		std::cout << "Dynamic Sprite position is " << sprite.getPosition().x << " , " << sprite.getPosition().y << std::endl;
		std::cout << "Dynamic Sprite scale is " << sprite.getScale().x << " , " << sprite.getScale().y << std::endl;

		b2Vec2 origin = m_body->GetLocalCenter();
		b2Vec2 position = m_body->GetPosition();
		float rotaion = m_body->GetAngle();

		std::cout << "Dynamic Collider origin " << origin.x << " , " << origin.y << std::endl;
		std::cout << "Dynamic Collider position " << position.x << " , " << position.y << std::endl;
		std::cout << "Dynamic Collider roatation " << rotaion << std::endl;

		std::cout << std::endl;
	}
}

RectAngleCollider::~RectAngleCollider()
{
	if (s_physicsWorld)
	{
		if (m_body)
		{
			s_physicsWorld->DestroyBody(m_body);
			m_body = nullptr;
		}
		delete m_contactListener;
	}
}


b2BodyDef* RectAngleCollider::getBodyDef()
{
	return &m_bodyDef;
}

b2Body* RectAngleCollider::getBody()
{
	return m_body;
}

b2PolygonShape* RectAngleCollider::getColliderShape()
{
	return &m_boxShape;
}

b2FixtureDef* RectAngleCollider::getFixtureDef()
{
	return &m_fixtureDef;;
}

b2Vec2 RectAngleCollider::getOffset()
{
	return m_offset;
}

b2Vec2* RectAngleCollider::getColliderScale()
{
	return &m_colliderSpriteScale;
}

b2Vec2 RectAngleCollider::getColliderPosition()
{
	return m_body->GetTransform().p;
}

void RectAngleCollider::setColliderPosition(float x, float y)
{
	m_body->SetTransform(b2Vec2(x, y), m_body->GetAngle());
}

void RectAngleCollider::printBodyPositionRotation()
{
	std::cout << getColliderPosition().x << " x axis " << getColliderPosition().y << " y axis " << std::endl;
	std::cout << m_body->GetAngle()<<" degrees " << std::endl;
}

void RectAngleCollider::printSpriteColliderPosition(sf::Sprite& sprite, int bodyState)
{
	if (bodyState == STATIC)
	{
		std::cout << "Static position is " << m_body->GetTransform().p.x << " , " << m_body->GetTransform().p.y << " VS Sprite position " <<
			sprite.getPosition().x << " , " << sprite.getPosition().y << std::endl;
	}
	else if (bodyState == DYNAMIC)
	{
		std::cout << "Dynamic position is " << m_body->GetTransform().p.x << " , " << m_body->GetTransform().p.y << " VS Sprite position " <<
											sprite.getPosition().x << " , " << sprite.getPosition().y << std::endl;
	}
}

void RectAngleCollider::debugRender(sf::RenderTarget& target)
{
	auto* fixture = m_body->GetFixtureList();
	while (fixture)
	{
		b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
		int32 vertexCount = poly->m_count;
		for (int32 i = 0; i < vertexCount; ++i) 
		{
			//they are polygen's vertices, you can use these to get the height / width
			b2Vec2 vertex = b2Mul(m_body->GetTransform(), poly->m_vertices[i]);

			sf::CircleShape circle(3.0f);
			circle.setFillColor(sf::Color::Green);
			circle.setPosition(vertex.x, vertex.y);
			target.draw(circle);
		}
		fixture = fixture->GetNext();
	}

	// DRAW COLLIDER BEGIN AND END
	auto outline = sf::RectangleShape(
		sf::Vector2f(
			getColliderScale()->x,
			getColliderScale()->y
		)
	);
	outline.setFillColor(sf::Color::Transparent);
	outline.setOutlineColor(sf::Color::Blue);
	outline.setOutlineThickness(3.0f);
	outline.setPosition(
		getColliderPosition().x,
		getColliderPosition().y
	);

	target.draw(outline);
}

void RectAngleCollider::applyMovement(float& movevmentSpeed, bool& moving, int direction)
{
	float move = movevmentSpeed * direction;

	b2Vec2 velocity = m_body->GetLinearVelocity();
	velocity.x = 0.0f;

	if (moving)
	{
		velocity.x += move;
	}
	
	m_body->SetLinearVelocity(velocity);

}

void RectAngleCollider::applyJump(float& jumpSpeed, bool& jumping)
{
	float jump = jumpSpeed * -1;

	b2Vec2 velocity = m_body->GetLinearVelocity();

	velocity.y = 0.0f;

	if (jumping)
	{
		velocity.y += jump;
	}

	m_body->SetLinearVelocity(velocity);


}


 GroundCheck* RectAngleCollider::m_contactListener;
 //std::vector<sf::Texture>* PlayerRunningAnimation::s_animFrameImg;


