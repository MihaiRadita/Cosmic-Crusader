#pragma once
#include "GameObjectConfig.h"
#include "physics/RectAngleCollider.h"

namespace ratchet
{
	class GameObject
	{
	public:

		//States
		Faction m_faction;
		MovementType m_movementType;
		ColliderType m_colliderType;
		ColliderShapeType m_colliderShapeType;

		//Transforms
		sf::Vector2f m_spawnPosition;
		sf::Vector2f m_spawnRotation;
		sf::Vector2f m_spawnScale;
		sf::Vector2f m_currentPosition;
		sf::Vector2f m_currentLocation;
		
		//Graphics
		std::string m_spritePath;
		sf::Sprite m_sprite;
		sf::Texture m_spriteTexture;

		//Physics
		sf::Vector2f m_colliderScaleMultipier;
		RectAngleCollider* m_collider;

		//Constructor
		GameObject(const GameObjectConfig& config);

		//Destructor
		~GameObject();

		virtual void init();
		virtual void update();
		virtual void destroy();
		virtual void updateInput();

		struct Ipput
		{

		};



	};

}

