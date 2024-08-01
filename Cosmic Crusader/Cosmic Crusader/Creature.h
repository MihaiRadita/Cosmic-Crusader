#pragma once
#include "GameObject.h"
#include "CreatureConfig.h"

namespace ratchet
{
	class Creature : public GameObject
	{
	public:

		//Character States
		Faction m_faction;
		MovementType m_movementType;
		ColliderType m_colliderType;
		ColliderShapeType m_colliderShapeType;

		//Character Transform
		sf::Vector2f m_spawnposition;
		sf::Vector2f m_spawnRotation;
		sf::Vector2f m_spawnScale;

		//Character Features
		float m_movementSpeed;
		float m_fallingSpeed;
		float m_jumpingSpeed;

		std::string m_spritePath;

		//Constructors
		Creature(CreatureConfig& config);

		//Destructors
		~Creature();

		//Other functions
		void updateInput() override;
	};
}


