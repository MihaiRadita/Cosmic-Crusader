#include "stdafx.h"
#include "CapsuleCollider.h"

#include "game/Player.h"
#include "SelfControlledCreature.h"

namespace ratchet
{

	CapsuleCollider::CapsuleCollider(sf::Sprite& sprite, const CapsuleColliderConfig& config) : ColliderBase(config)
	{
		initVariables(sprite, config);
	}

	void CapsuleCollider::initVariables(sf::Sprite& sprite, const CapsuleColliderConfig& config)
	{
		
		isColliderSetDestroy = false;
		

		m_JumpOverBottomRaycastOffsetX = config.m_JumpOverBottomRaycastOffsetX;
		m_JumpOverBottomRaycastOffsetY = config.m_JumpOverBottomRaycastOffsetY;

		m_JumpOverTopRaycastOffsetX = config.m_JumpOverTopRaycastOffsetX;
		m_JumpOverTopRaycastOffsetY = config.m_JumpOverTopRaycastOffsetY;

		m_isGroundRaycastOffset = config.m_isGroundRaycastOffset;

		m_checkFallingRiskRaycastStartOffsetX = config.m_checkFallingRiskRaycastStartOffsetX;
		m_checkFallingRiskRaycastStartOffsetY = config.m_checkFallingRiskRaycastStartOffsetY;

		m_checkFallingRiskRaycastEndOffsetX = config.m_checkFallingRiskRaycastEndOffsetX;
		m_checkFallingRiskRaycastEndOffsetY = config.m_checkFallingRiskRaycastEndOffsetY;

		m_bodyDef.type = config.m_bodyDef.type;
		m_bodyDef.fixedRotation = config.m_bodyDef.fixedRotation;

		m_massValue = config.m_massValue;
		
		
		m_scaleX = 1.0f;
		m_scaleY = 1.0f;

		if (config.m_radius.has_value() && config.m_height.has_value())
		{
			m_height = config.m_height.value();
			m_radius = config.m_radius.value();
		}
		else
		{
			m_height = sprite.getGlobalBounds().height;
			m_radius = sprite.getGlobalBounds().width / 2.0f;
		}


		if (config.m_origin.has_value())
		{
			m_origin = config.m_origin.value();
		}
		else
		{
			m_origin = b2Vec2(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f);
		}

		m_bodyDef.position.Set(sprite.getPosition().x, sprite.getPosition().y);

		if (!s_physicsWorld)
		{
			m_body = nullptr;
			return;
		}

		m_body = s_physicsWorld->CreateBody(&m_bodyDef);

		if (m_massValue != 0.0f)
		{
			m_massData.mass = m_massValue;

			m_body->SetMassData(&m_massData);
		}

		m_body->SetGravityScale(config.m_gravityScale);
		m_body->SetLinearDamping(config.m_linearDamping);
		m_body->SetAngularDamping(config.m_angularDamping);

		m_userDataName = static_cast<short>(config.m_layer);

		// Bottom Circle
		m_bottomCircleShape.m_radius = getGlobalRadius();
		m_bottomCircleShape.m_p.Set(m_origin.x, m_origin.y + (getGlobalHeight() / 2.0f) - getGlobalRadius());
		m_fixtureDef.shape = &m_bottomCircleShape;
		m_fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&m_userDataName);
		m_fixtureDef.isSensor = config.m_fixtureDef.isSensor;
		m_body->CreateFixture(&m_fixtureDef);
		// Top Circle
		m_topCircleShape.m_radius = getGlobalRadius();
		m_topCircleShape.m_p.Set(m_origin.x, m_origin.y - (getGlobalHeight() / 2.0f) + getGlobalRadius());
		m_fixtureDef.shape = &m_topCircleShape;
		m_fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&m_userDataName);
		m_fixtureDef.isSensor = config.m_fixtureDef.isSensor;
		m_body->CreateFixture(&m_fixtureDef);
		// Center Box
		const auto centerBoxHeight = std::abs(m_bottomCircleShape.m_p.y - m_topCircleShape.m_p.y);
		const auto centerBoxHalfHeight = centerBoxHeight / 2.0f;
		m_boxShape.SetAsBox(getGlobalRadius(), centerBoxHalfHeight, m_origin, m_body->GetAngle());
		m_fixtureDef.shape = &m_boxShape;
		m_fixtureDef.density = config.m_fixtureDef.density;
		m_fixtureDef.friction = config.m_fixtureDef.friction;
		m_fixtureDef.restitution = config.m_fixtureDef.restitution;
		m_fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&m_userDataName);
		m_fixtureDef.isSensor = config.m_fixtureDef.isSensor;
		m_body->CreateFixture(&m_fixtureDef);

		if (m_bodyDef.type == b2_staticBody)
		{
#ifdef IS_RATCHET_DEBUG
			b2Vec2 origin = m_body->GetLocalCenter();
			b2Vec2 position = m_body->GetTransform().p;
			float rotation = m_body->GetAngle();
#endif
		}
		else if (m_bodyDef.type == b2_dynamicBody)
		{
#ifdef IS_RATCHET_DEBUG
			b2Vec2 origin = m_body->GetLocalCenter();
			b2Vec2 position = m_body->GetPosition();
			float rotation = m_body->GetAngle();
#endif
		}

	}

	CapsuleCollider::~CapsuleCollider()
	{
		if (s_physicsWorld)
		{
			if (m_body)
			{
				s_physicsWorld->DestroyBody(m_body);
				m_body = nullptr;
			}
		
		}
	}

	b2BodyDef* CapsuleCollider::getBodyDef()
	{
		return &m_bodyDef;
	}

	b2PolygonShape* CapsuleCollider::getColliderBoxShape()
	{
		return &m_boxShape;
	}

	b2CircleShape* CapsuleCollider::getBottomColliderCircleShape()
	{
		return &m_bottomCircleShape;
	}

	b2CircleShape* CapsuleCollider::getTopColliderCircleShape()
	{
		return &m_topCircleShape;
	}

	b2FixtureDef* CapsuleCollider::getFixtureDef()
	{
		return &m_fixtureDef;
	}

	b2Vec2 CapsuleCollider::getOffset()
	{
		return m_offset;
	}

	b2Vec2 CapsuleCollider::getColliderPosition()
	{
		if (!m_body)
		{
			return b2Vec2_zero;
		}
		return m_body->GetTransform().p;
	}

	float CapsuleCollider::getTopCircleRadius()
	{
		return m_topCircleShape.m_radius;
	}

	float CapsuleCollider::getBottomCircleRadius()
	{
		return m_bottomCircleShape.m_radius;
	}

	void CapsuleCollider::RestartColliderFeatures(sf::Sprite& sprite, const CapsuleColliderConfig& config)
	{
		m_bodyDef.position.Set(sprite.getPosition().x, sprite.getPosition().y);

	}

	CapsuleColliderConfig::CapsuleColliderConfig()
	{
		m_collierFacingDirectionX = 0.0f;
		m_colliderFacingDirectionY = 0.0f;
		m_JumpOverBottomRaycastOffsetX = 0.0f;
		m_JumpOverBottomRaycastOffsetY = 0.0f;
		m_JumpOverTopRaycastOffsetX = 0.0f;
		m_JumpOverTopRaycastOffsetY = 0.0f;
	}


//#ifdef IS_RATCHET_DEBUG
	void CapsuleCollider::printBodyPositionRotation()
	{
		TRACE_CHANNEL("COLLISION", getColliderPosition().x, " x axis ", getColliderPosition().y, " y axis ");
		TRACE_CHANNEL("COLLISION", m_body->GetAngle(), " degrees ");
	}

	void CapsuleCollider::printSpriteColliderPosition(sf::Sprite& sprite, int bodyState)
	{
		if (!m_body)
		{
			return;
		}

		if (bodyState == STATIC)
		{
			TRACE_CHANNEL("COLLISION", "Static position is ", m_body->GetTransform().p.x, " , ", m_body->GetTransform().p.y, " VS Sprite position ",
				sprite.getPosition().x, " , ", sprite.getPosition().y);
		}
		else if (bodyState == DYNAMIC)
		{
			TRACE_CHANNEL("COLLISION", "Dynamic position is ", m_body->GetTransform().p.x, " , ", m_body->GetTransform().p.y, " VS Sprite position ",
				sprite.getPosition().x, " , ", sprite.getPosition().y);
		}
	}

	void CapsuleCollider::debugRender(sf::RenderTarget& target)
	{
//#ifdef IS_RATCHET_DEBUG
//		if (!m_debugDraw) return;
//#endif
		if (!m_body)
		{
			return;
		}

		const auto worldOrigin = getColliderPosition() + m_origin;

		// Origin
		{
			auto circleShape = sf::CircleShape(getGlobalRadius() * 0.7f);
			circleShape.setFillColor(sf::Color::Magenta);
			const auto position = worldOrigin;
			circleShape.setPosition(position.x - circleShape.getRadius(), position.y - circleShape.getRadius());
			target.draw(circleShape);
		}

		// DRAW COLLIDER BEGIN AND END
		// Center Box
		{
			auto rectangleShape = sf::RectangleShape();
			rectangleShape.setFillColor(sf::Color::Transparent);
			rectangleShape.setOutlineColor(sf::Color::Green);
			rectangleShape.setOutlineThickness(0.03f);

			float maxWidth = std::numeric_limits<float>().min();
			float maxHeight = std::numeric_limits<float>().min();
			for (int i = 0; i < 4; i++)
			{
				if (i > 0)
				{
					const auto width = std::abs(m_boxShape.m_vertices[i].x - m_boxShape.m_vertices[i - 1].x);
					if (width > maxWidth)
					{
						maxWidth = width;
					}

					const auto height = std::abs(m_boxShape.m_vertices[i].y - m_boxShape.m_vertices[i - 1].y);
					if (height > maxHeight)
					{
						maxHeight = height;
					}
				}
			}
			rectangleShape.setSize(sf::Vector2f(maxWidth, maxHeight));
			rectangleShape.setPosition(worldOrigin.x - maxWidth / 2.0f, worldOrigin.y - maxHeight / 2.0f);
			target.draw(rectangleShape);
		}
		// Bottom Circle
		{
			auto circleShape = sf::CircleShape(m_bottomCircleShape.m_radius);
			circleShape.setFillColor(sf::Color::Transparent);
			circleShape.setOutlineColor(sf::Color::Green);
			circleShape.setOutlineThickness(0.03f);
			const auto position = getColliderPosition() + m_bottomCircleShape.m_p;
			circleShape.setPosition(position.x - circleShape.getRadius(), position.y - circleShape.getRadius());
			target.draw(circleShape);
		}
		// Top Circle
		{
			auto circleShape = sf::CircleShape(m_topCircleShape.m_radius);
			circleShape.setFillColor(sf::Color::Transparent);
			circleShape.setOutlineColor(sf::Color::Green);
			circleShape.setOutlineThickness(0.03f);
			const auto position = getColliderPosition() + m_topCircleShape.m_p;
			circleShape.setPosition(position.x - circleShape.getRadius(), position.y - circleShape.getRadius());
			target.draw(circleShape);
		}
		// Body
		{
			auto bodyCircle = sf::CircleShape(0.01f);
			bodyCircle.setFillColor(sf::Color::Yellow);
			bodyCircle.setPosition(worldOrigin.x, worldOrigin.y);
			target.draw(bodyCircle);
		}

		b2Vec2 startPointMiddle = b2Vec2{};
		b2Vec2 endPointMiddle = b2Vec2{};
		getMiddlePointsForRaycast(startPointMiddle.x, startPointMiddle.y, endPointMiddle.x, endPointMiddle.y);

		sf::Vertex rayCastMiddle[] = { sf::Vertex(sf::Vector2f(startPointMiddle.x, startPointMiddle.y), sf::Color::Green), sf::Vertex(sf::Vector2f(startPointMiddle.x, endPointMiddle.y), sf::Color::Green) };
		target.draw(rayCastMiddle, 2, sf::Lines);

		b2Vec2 startPointMiddleJump = b2Vec2{};
		b2Vec2 endPointMiddleJump = b2Vec2{};
		//float direction = 1.0f;
		getJumpOverPlatformsBottomRaycastPoints(startPointMiddleJump.x, startPointMiddleJump.y, endPointMiddleJump.x, endPointMiddleJump.y, m_collierFacingDirectionX);

		sf::Vertex raycasMiddelJumpOver[] = { sf::Vertex(sf::Vector2f(startPointMiddleJump.x, startPointMiddleJump.y), sf::Color::Red), sf::Vertex(sf::Vector2f(endPointMiddleJump.x, startPointMiddleJump.y), sf::Color::Red) };
		target.draw(raycasMiddelJumpOver, 2, sf::Lines);

		b2Vec2 startPointCheckMiddleJump = b2Vec2{};
		b2Vec2 endPointCheckMiddleJump = b2Vec2{};

		getJumpOverPlatformsTopRaycastPoints(startPointCheckMiddleJump.x, startPointCheckMiddleJump.y, endPointCheckMiddleJump.x, endPointCheckMiddleJump.y, m_collierFacingDirectionX);
		sf::Vertex raycasMiddelJumpOverCheck[] = { sf::Vertex(sf::Vector2f(startPointCheckMiddleJump.x, startPointCheckMiddleJump.y), sf::Color::Yellow), sf::Vertex(sf::Vector2f(endPointCheckMiddleJump.x, startPointCheckMiddleJump.y), sf::Color::Yellow) };
		target.draw(raycasMiddelJumpOverCheck, 2, sf::Lines);

		b2Vec2 sartPointCheckFallingRisk = b2Vec2{};
		b2Vec2 endPointCheckFallingRisk = b2Vec2{};

		getCheckFallingRiscRaycastPoints(sartPointCheckFallingRisk.x, sartPointCheckFallingRisk.y, endPointCheckFallingRisk.x, endPointCheckFallingRisk.y, m_collierFacingDirectionX);
		sf::Vertex raycastCheckFallingRisk[] = { sf::Vertex(sf::Vector2f(sartPointCheckFallingRisk.x,sartPointCheckFallingRisk.y), sf::Color::Blue) , sf::Vertex(sf::Vector2f(sartPointCheckFallingRisk.x,endPointCheckFallingRisk.y), sf::Color::Blue) };
		target.draw(raycastCheckFallingRisk, 2, sf::Lines);
	}
//#endif
		void CapsuleCollider::getMiddlePointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const
		{
			if (!m_body)
			{
				return;
			}

			ColliderBase::getMiddlePointsForRaycast(xStart, yStart, xEnd, yEnd);

			b2Vec2 playerPosition = m_body->GetPosition();

			xStart =  playerPosition.x +  m_bottomCircleShape.m_p.x;
			yStart = playerPosition.y + m_bottomCircleShape.m_p.y;

			xEnd = xStart;
			yEnd = yStart + m_bottomCircleShape.m_radius + m_isGroundRaycastOffset;
		}


		void CapsuleCollider::getJumpOverPlatformsBottomRaycastPoints(float& xStart, float& yStart, float& xEnd, float& yEnd, float direction) const
		{
			if (!m_body)
			{
				return;
			}

			ColliderBase::getJumpOverPlatformsBottomRaycastPoints(xStart, yStart, xEnd, yEnd, direction);

			b2Vec2 playerPosition = m_body->GetPosition();

			xStart = playerPosition.x + m_bottomCircleShape.m_p.x;

			yStart = playerPosition.y + m_bottomCircleShape.m_p.y + m_JumpOverBottomRaycastOffsetY;

			xEnd = xStart + (m_bottomCircleShape.m_radius + m_JumpOverBottomRaycastOffsetX) * direction;

			yEnd = yStart;
		}

		void CapsuleCollider::getJumpOverPlatformsTopRaycastPoints(float& xStart, float& yStart, float& xEnd, float& yEnd, float direction) const
		{

			if (!m_body)
			{
				return;
			}

			ColliderBase::getJumpOverPlatformsTopRaycastPoints( xStart, yStart, xEnd, yEnd, direction);

			b2Vec2 playerPosition = m_body->GetPosition();

			xStart = playerPosition.x + m_bottomCircleShape.m_p.x;

			yStart = playerPosition.y + m_topCircleShape.m_p.y - m_JumpOverTopRaycastOffsetY;

			xEnd = xStart + (m_bottomCircleShape.m_radius + m_JumpOverTopRaycastOffsetX) * direction;

			yEnd = yStart;

		}

		bool CapsuleCollider::performGroundRayCast(sf::Sprite& sprite)
		{
			
			if (!m_body || !s_physicsWorld)
			{
				return false;
			}
			
			b2Vec2 startPointMiddle = b2Vec2{};
			b2Vec2 endPointMiddle = b2Vec2{};
			getMiddlePointsForRaycast(startPointMiddle.x, startPointMiddle.y, endPointMiddle.x, endPointMiddle.y);

			GroundRayCastCallBack callbackMiddle(m_body);

			s_physicsWorld->RayCast(&callbackMiddle, startPointMiddle, endPointMiddle);

			if (SelfControlledCreature* self = dynamic_cast<SelfControlledCreature*>(m_obj))
			{
				float speed = self->m_movementSpeed;
				bool canJumpOver = self->m_canJumpOver;
			}
			else if (Player* pl = dynamic_cast<Player*>(m_obj))
			{
				float  angledeg = pl->m_movementSpeed;
			}
			
			if (callbackMiddle.m_fraction <= 1.0f && callbackMiddle.m_hit)
			{
				return true;
			}
			
			return false;
		}

		bool CapsuleCollider::performJumpOverPlatformsRaycast(sf::Sprite& sprite, float& direction)
		{

			if (!m_body || !s_physicsWorld)
			{
				return false;
			}
			
			b2Vec2 sartPointMiddleJump = b2Vec2{};
			b2Vec2 endPointMiddleJump = b2Vec2{};

			getJumpOverPlatformsBottomRaycastPoints(sartPointMiddleJump.x, sartPointMiddleJump.y, endPointMiddleJump.x, endPointMiddleJump.y, direction);

			JumpOverPlatformsRayCastCallBack callBackMiddleJumpOver(m_body);

			s_physicsWorld->RayCast(&callBackMiddleJumpOver, sartPointMiddleJump, endPointMiddleJump);

			if (SelfControlledCreature* self = dynamic_cast<SelfControlledCreature*>(m_obj))
			{
				float speed = self->m_movementSpeed;
				bool canJumpOver = self->m_canJumpOver;
			}

			if (callBackMiddleJumpOver.m_hit)
			{
				if (callBackMiddleJumpOver.m_fraction <= 1.0f)
				{

					b2Vec2 sartPointMiddleJumpCheck = b2Vec2{};
					b2Vec2 endPointMiddleJumpCheck = b2Vec2{};

					JumpOverPlatformsRayCastCallBack callBackMiddleJumpOver2(m_body);

					getJumpOverPlatformsTopRaycastPoints(sartPointMiddleJumpCheck.x, sartPointMiddleJumpCheck.y, endPointMiddleJumpCheck.x, endPointMiddleJumpCheck.y, direction);

					s_physicsWorld->RayCast(&callBackMiddleJumpOver2, sartPointMiddleJumpCheck, endPointMiddleJumpCheck);

					callBackMiddleJumpOver2.m_fraction;

					if (callBackMiddleJumpOver2.m_hit == false)
					{
						return true;
					}

					return false;
				}
			}

			return false;
		}

		void CapsuleCollider::getCheckFallingRiscRaycastPoints(float& xStart, float& yStart, float& xEnd, float& yEnd, float direction) const
		{
			if (!m_body)
			{
				return;
			}

			ColliderBase::getCheckFallingRiscRaycastPoints(xStart, yStart, xEnd, yEnd, direction);

			b2Vec2 characterPosition = m_body->GetPosition();

			xStart = characterPosition.x + m_bottomCircleShape.m_p.x + m_checkFallingRiskRaycastStartOffsetX * direction;
			yStart = characterPosition.y + m_bottomCircleShape.m_p.y + m_checkFallingRiskRaycastStartOffsetY;

			xEnd = xStart;
			yEnd = yStart + m_checkFallingRiskRaycastEndOffsetY;
		}

		bool CapsuleCollider::performCheckFallingRiskRaycast(sf::Sprite& sprite, float& direction)
		{
			if (!m_body || !s_physicsWorld)
			{
				return false;
			}
			
			b2Vec2 startCheckFallingRisk = b2Vec2{};
			b2Vec2 endCheckFallingRisk = b2Vec2{};

			getCheckFallingRiscRaycastPoints(startCheckFallingRisk.x, startCheckFallingRisk.y, endCheckFallingRisk.x, endCheckFallingRisk.y, direction);

			CheckFallingRiskRaycastCallBack callbackCheckFallingRisk(m_body);

			s_physicsWorld->RayCast(&callbackCheckFallingRisk, startCheckFallingRisk, endCheckFallingRisk);

			if (callbackCheckFallingRisk.m_fraction < 1.0f && callbackCheckFallingRisk.m_hit)
			{
				return true;
			}

			return false;
			
		}
}

