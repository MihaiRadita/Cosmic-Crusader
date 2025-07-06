
#include "stdafx.h"
#include "GameObject.h"


namespace ratchet
{
	sf::Sprite ratchet::GameObject::getSprite()
	{
		return m_sprite;
	}

	sf::Vector2f ratchet::GameObject::getPosition()
	{
		return m_position;
	}

	float ratchet::GameObject::getRotation()
	{
		return m_rotation;
	}

	sf::Vector2f ratchet::GameObject::getScale()
	{
		return m_scale;
	}

	sf::FloatRect ratchet::GameObject::getBounds()
	{
		return m_sprite.getGlobalBounds();
	}

	sf::FloatRect GameObject::getLocalBounds()
	{
		return m_sprite.getLocalBounds();
	}

	ColliderBase* GameObject::getCollider()
	{
		return m_collider;
	}


	GameObject* GameObject::findGameObject(const b2Body* body)
	{
		for (auto* obj : s_gameObjects)
		{
			if (auto* collider = obj->getCollider())
			{
				if (auto* colliderBody = collider->getBody())
				{
					if (colliderBody == body)
					{
						return obj;
					}

				}
			}
		}
		return nullptr;
	}


	GameObject::GameObject()
	{
	}

	ratchet::GameObject::GameObject(const GameObjectConfig& config)
	{
#ifdef IS_RATCHET_DEBUG
		m_debugDraw = config.m_debugDraw;
#endif

		//States
		m_faction = config.m_Faction;
		m_colliderType = config.m_colliderType;
		m_colliderShapeType = config.m_colliderShapeType;
		m_movementType = config.m_movementType;

		//Transforms
		m_position = config.position;
		m_rotation = config.rotation;
		m_scale = config.scale;

		m_startSpritePath = config.startSpriteTexturePath;


		//Sprites and Terxtures

		if (m_spriteTexture.loadFromFile(m_startSpritePath) == false)
		{
#ifdef IS_RATCHET_DEBUG
			TRACE_CHANNEL(TR_GAMEOBJECT_INIT, "ERROR::PLAYER COULD NOT LOAD THE TEXTURE SHEET");
#endif
		}


		m_sprite.setTexture(m_spriteTexture);
		m_sprite.setPosition(m_position.x, m_position.y);
		m_sprite.setRotation(m_rotation);
		m_sprite.setScale(m_scale.x, m_scale.y);

		if (config.m_colliderConfig->m_layer == PhysiscsLayer::Player)
		{
			m_collider = new ratchet::CapsuleCollider(m_sprite, static_cast<const CapsuleColliderConfig&>(*config.m_colliderConfig));

		}
		else if (config.m_colliderConfig->m_layer == PhysiscsLayer::Platforms)
		{
			m_collider = new ratchet::RectAngleCollider(m_sprite, static_cast<const RectAngleColliderConfig&>(*config.m_colliderConfig));
		}
		else if (config.m_colliderConfig->m_layer == PhysiscsLayer::Items)
		{
			m_collider = new ratchet::RectAngleCollider(m_sprite, static_cast<const RectAngleColliderConfig&>(*config.m_colliderConfig));
		}
		else if (config.m_colliderConfig->m_layer == PhysiscsLayer::Projectiles)
		{
			m_collider = new ratchet::RectAngleCollider(m_sprite, static_cast<const RectAngleColliderConfig&>(*config.m_colliderConfig));
		}
	}

	ratchet::GameObject::~GameObject()
	{
		delete m_collider;
	}

	void ratchet::GameObject::init()
	{
		initGraphics();
		initPhyics();
	}

	void ratchet::GameObject::initGraphics()
	{
	}

	void ratchet::GameObject::initPhyics()
	{
	}

	void ratchet::GameObject::update()
	{
	}

	void ratchet::GameObject::render(sf::RenderTarget& target)
	{
#ifdef IS_RATCHET_DEBUG
		if (m_collider)
		{
			m_collider->debugRender(target);
		}

		if (m_debugDraw)
		{
			// DRAW CIRCLE AT POSITION
			{
				auto circleShape = sf::CircleShape(0.05f);
				circleShape.setFillColor(sf::Color::Transparent);
				circleShape.setOutlineColor(sf::Color::Cyan);
				circleShape.setOutlineThickness(0.03f);
				const auto position = getPosition();
				circleShape.setPosition(position.x - circleShape.getRadius(), position.y - circleShape.getRadius());
				target.draw(circleShape);
			}

			// DRAW SPRITE BOUNDS
			{
				auto spriteOutline = sf::RectangleShape(sf::Vector2f(
					m_sprite.getGlobalBounds().width,
					m_sprite.getGlobalBounds().height)
				);
				spriteOutline.setFillColor(sf::Color::Transparent);
				spriteOutline.setOutlineColor(sf::Color::Red);
				spriteOutline.setOutlineThickness(0.01f);
				spriteOutline.setPosition(
					m_sprite.getPosition().x,
					m_sprite.getPosition().y);
				target.draw(spriteOutline);
			}
		}
#endif

		target.draw(m_sprite);
	}

	GameObject* GameObject::findGameObjectByBody(const b2Body* body)
	{
		for (auto* gameObject : s_gameObjects) 
		{
			if (gameObject != nullptr && gameObject->m_collider != nullptr && gameObject->m_collider->getBody() == body)
			{
				return gameObject;
			}
		}

		return nullptr; 
	}

	void GameObject::addGameObjectoDestory(GameObject* object)
	{
		if (object != nullptr)
		{
			s_gameObjectsToDestroy.push(object);
		}
	}

	void GameObject::setPosition(const sf::Vector2f position)
	{
		m_position = position + sf::Vector2f(m_collider->getColliderOrigin().x, m_collider->getColliderOrigin().y);
		m_sprite.setPosition(position);
	}

	void GameObject::setRotation(const float angle)
	{
		m_rotation = angle;
		m_sprite.setRotation(m_rotation);
	}

	void GameObject::SetPositionAndRotation(const sf::Vector2f& position, const float& rotationDegrees)
	{
		float angleRad = rotationDegrees * b2_pi / 180.f;

		if (m_collider)
		{
			m_collider->getBody()->SetTransform(b2Vec2(position.x, position.y), angleRad);
		}

		setPosition(position);
		setRotation(rotationDegrees);

	}

	void GameObject::DestroyGameObject()
	{
		if (this == nullptr) {
			return;
		}

		if (m_collider) {
			delete m_collider;  
			m_collider = nullptr;
		}

		auto it = std::find(s_gameObjects.begin(), s_gameObjects.end(), this);
		if (it != s_gameObjects.end()) {
			s_gameObjects.erase(it);
		}

		delete this; 
		TRACE_CHANNEL(TR_GAMEOBJECT_INIT, "The Object HAS BEEN DESTROYED!");
	}

	void GameObject::RemoveGameObjectFromList()
	{
		for (auto it = s_gameObjects.begin(); it != s_gameObjects.end(); ++it)
		{
			if (*it == this)
			{
				s_gameObjects.erase(it);
				break; 
			}
		}
	}

	void GameObject::clearQueuedObjectsToDestroy()
	{
		while (s_gameObjectsToDestroy.empty() == false)
		{
			auto* nextGameObject = s_gameObjectsToDestroy.front();
			if (nextGameObject)
			{
				nextGameObject->DestroyGameObject();
			}
			nextGameObject = nullptr;
			s_gameObjectsToDestroy.pop();
		}
	}

	void ratchet::GameObject::destroy()
	{
	}

	void ratchet::GameObject::updateInput()
	{

	}

	void ratchet::GameObject::updatePhysics()
	{
	}

	void ratchet::GameObject::updateRotation()
	{
	}

	void ratchet::GameObject::updateMovement()
	{
	}

	void GameObject::updateJump()
	{
	}

	void GameObject::updateRunningJump()
	{
	}

	void GameObject::updateWeaponSelection()
	{
	}

	void GameObject::OnCollisionEnter(GameObject* obj)
	{
	}

	void GameObject::OnCollisionExit(GameObject* obj)
	{
	}

	void GameObject::OnSensorEnter(GameObject* obj)
	{
	}

	void GameObject::OnSensorExit(GameObject* obj)
	{
	}

	const sf::FloatRect ratchet::GameObject::getBounds() const
	{
		return m_sprite.getGlobalBounds();
	}

	void ratchet::GameObject::Input::resetMovementControls()
	{
		x = 0;
		y = 0;
	}

	void ratchet::GameObject::Input::resetJumpControls()
	{
		isJump = false;
	}

	void GameObject::Input::resetControls()
	{ 
		resetMovementControls();
		resetJumpControls();
	}

	std::vector<GameObject*>GameObject ::s_gameObjects;
	std::queue<GameObject*>GameObject::s_gameObjectsToDestroy;

}
