#include "stdafx.h"
#include "RectAngleCollider.h"

//Listeners

void GroundCheck::BeginContact(b2Contact* contact)
{

}

void GroundCheck::EndContact(b2Contact* contact)
{
}

GroundRayCastCallBack::GroundRayCastCallBack(b2Body* ignoredBody)
{
	m_hit = false;
	m_fraction = 1.0f;

	m_ignoredBody = ignoredBody;
}
	
float GroundRayCastCallBack::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
{
	if (fixture)
	{
		b2Body* body = fixture->GetBody();
		if (body == m_ignoredBody)
		{
			return -1.0f;
		}
		const std::string* fixtureUserData = reinterpret_cast<const std::string*>(fixture->GetUserData().pointer);
		if (fixtureUserData && *fixtureUserData == "Tile") {
			m_hit = true;
			m_point = point;
			m_normal = normal;
			m_fraction = fraction;
			return fraction;
		}
	}

	//m_hit = false;
	return -1.0f;
}


std::string GroundCheck:: getCollisionSide(const b2Vec2& localPoint, const b2AABB& aabb) {
	
	float epsilon = 0.1f;
	float top = aabb.upperBound.y;
	float bottom = aabb.lowerBound.y;
	float left = aabb.lowerBound.x ;
	float right = aabb.upperBound.x ;

	std::cout << std::endl;
	std::cout << "Local point: (" << localPoint.x << ", " << localPoint.y << ")" << std::endl;
	std::cout << "AABB: top = " << top << ", bottom = " << bottom << ", left = " << left << ", right = " << right << std::endl;


	if (localPoint.y >= bottom)
		return "bottom";
	if (localPoint.y <= top)
		return "top";
	if (localPoint.x <= left)
		return "left";
	if (localPoint.x >= right)
		return "right";

	return "unknown";
}
		

RectAngleCollider::RectAngleCollider(sf::Sprite& sprite, int bodyTypeState, int entityType)
{
	initVariables(sprite, bodyTypeState, entityType);
}

void RectAngleCollider::initVariables(sf::Sprite& sprite, int bodyTypeState , int entityType)
{
	//Body Def Type
	m_offset = b2Vec2(20.0f, 0.0f);

	b2Vec2 tilePosition;

	b2Vec2 playerPosition;

	if (!m_contactListener)
	{
		m_contactListener = new GroundCheck();
		s_physicsWorld->SetContactListener(m_contactListener);
	}

	//m_colliderOrigin = b2Vec2(sprite.getOrigin().x / 2.0f, sprite.getOrigin().y / 2.0f);
	m_colliderOrigin = b2Vec2(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	m_colliderSpriteScale = b2Vec2(
		sprite.getLocalBounds().width, 
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
		m_fixtureDef.restitution = 0.0f;
	}
	else if (bodyTypeState == STATIC)
	{
		m_fixtureDef.density = 0.f;
		m_fixtureDef.friction = 0.3f;
		m_fixtureDef.restitution = 0.f;
	}
	if (entityType == PLAYER)
	{
		userDataName = new std::string("Player");
		m_fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(userDataName);

		playerPosition = m_body->GetPosition();

	}
	else if (entityType == TILE)
	{
		userDataName = new std::string("Tile");
		m_fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(userDataName);

		 tilePosition = m_body->GetPosition();
	}


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
		delete userDataName;
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

	auto bodyPosition = sf::CircleShape(3.f);
	bodyPosition.setFillColor(sf::Color::Yellow);
	bodyPosition.setPosition(m_body->GetPosition().x, m_body->GetPosition().y);

	sf::Vertex line[] = { sf::Vertex(sf::Vector2f(500.f, 10.f), sf::Color::Green), sf::Vertex(sf::Vector2f(700.f, 10.f), sf::Color::Green) };


	float playerWidth = m_colliderSpriteScale.x;
	float playerHeight = m_colliderSpriteScale.y;
	b2Vec2 playerPosition = m_body->GetPosition();

	b2Vec2 startPointLeft = b2Vec2(playerPosition.x + 2.f, playerPosition.y + (playerHeight / 2.f));
	b2Vec2 endPointLeft = b2Vec2(startPointLeft.x, startPointLeft.y + ((playerHeight / 2.f)) + 1.5f);

	sf::Vertex rayCastLeft[] = { sf::Vertex(sf::Vector2f(startPointLeft.x, startPointLeft.y), sf::Color::Green), sf::Vertex(sf::Vector2f(startPointLeft.x, endPointLeft.y), sf::Color::Green) };

	auto pointLeftStart = sf::CircleShape(3.0f);
	pointLeftStart.setFillColor(sf::Color::Red);
	pointLeftStart.setPosition(startPointLeft.x, startPointLeft.y);

	b2Vec2 startPointRight = b2Vec2((playerPosition.x + playerWidth) - 2.f, playerPosition.y + (playerHeight / 2.f));
	b2Vec2 endPointRight = b2Vec2(startPointRight.x, startPointRight.y + ((playerHeight / 2.f)) + 1.5f);

	sf::Vertex rayCastRight[] = { sf::Vertex(sf::Vector2f(startPointRight.x, startPointRight.y), sf::Color::Green), sf::Vertex(sf::Vector2f(startPointRight.x, endPointRight.y), sf::Color::Green) };

	auto pointRightStart = sf::CircleShape(3.0f);
	pointRightStart.setFillColor(sf::Color::Red);
	pointRightStart.setPosition(startPointRight.x, startPointRight.y);

	target.draw(outline);
	target.draw(bodyPosition);
	target.draw(line, 2, sf::Lines);
	target.draw(rayCastLeft,2, sf::Lines);
	target.draw(rayCastRight, 2, sf::Lines);
	target.draw(pointLeftStart);
	target.draw(pointRightStart);
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

bool RectAngleCollider::performGroundRayCast(sf::Sprite& sprite)
{
	float playerWidth = sprite.getGlobalBounds().width;
	float playerHeight = sprite.getGlobalBounds().height;
	b2Vec2 playerPosition = m_body->GetPosition();

	b2Vec2 startPointLeft = b2Vec2(playerPosition.x + 2.f, playerPosition.y + (playerHeight / 2.f));
	b2Vec2 endPointLeft = b2Vec2(startPointLeft.x, startPointLeft.y + ((playerHeight / 2.f)) + 1.5f);

	b2Vec2 startPointRight = b2Vec2((playerPosition.x + playerWidth) - 2.f, playerPosition.y + (playerHeight / 2.f));
	b2Vec2 endPointRight = b2Vec2(startPointRight.x, startPointRight.y + ((playerHeight / 2.f)) + 1.5f);

	GroundRayCastCallBack callbackLeft(m_body);
	s_physicsWorld->RayCast(&callbackLeft, startPointLeft, endPointLeft);

	GroundRayCastCallBack callbackRight(m_body);
	s_physicsWorld->RayCast(&callbackRight, startPointRight, endPointRight);

	if ((callbackLeft.m_fraction <=1.0f || callbackRight.m_fraction <= 1.0f) && (callbackLeft.m_hit || callbackRight.m_hit))
	{
			std::cout << "Victory " << std::endl;
			return true;
	}
		
	std::cout << "HIT : " << callbackLeft.m_hit;
	return false;
}

 GroundCheck* RectAngleCollider::m_contactListener;




