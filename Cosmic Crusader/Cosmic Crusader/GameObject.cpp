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

	ColliderBase* GameObject::getCollider()
	{
		return m_collider;
	}

	ratchet::GameObject::GameObject(const GameObjectConfig& config)
	{
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
			//std::cout << "ERROR::PLAYER COULD NOT LOAD THE TEXTURE SHEET" << std::endl;
#endif
		}


		m_sprite.setTexture(m_spriteTexture);
		m_sprite.setPosition(m_position.x, m_position.y);
		m_sprite.setRotation(m_rotation);
		m_sprite.setScale(m_scale.x, m_scale.y);


		if (config.m_colliderConfig->m_layer == PhysiscsLayer::Player)
		{
			m_collider = new ratchet::RectAngleCollider(m_sprite, static_cast<const RectAngleColliderConfig&>(*config.m_colliderConfig));

		}
		else if (config.m_colliderConfig->m_layer == PhysiscsLayer::Platforms)
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
		m_collider->debugRender(target);

		// DRAW SPRITE BOUNDS
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

	void GameObject::setPosition(const sf::Vector2f position)
	{
		m_position = position;
		m_sprite.setPosition(position);
	}

	void GameObject::setRotation(const float angle)
	{
		m_rotation = angle;
		m_sprite.setRotation(m_rotation);
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

}
