#pragma once

#include "animations/Animator.h"
#include "animations/AnimationIdle.h"
#include "animations/AnimationRun.h"
#include "animations/AnimationJump.h"
#include "animations/AnimationJumpRun.h"

#include "physics/RectAngleCollider.h"

#include "Creature.h"

namespace ratchet
{
	class Player : public Creature
	{
	private:

		//Animations Destroy
		void destroyPlayerAnimations();

		// Variables
		float m_gravity;

		std::vector<sf::Event> m_playerEvents;
	public:

		//Constructors
		Player(const CreatureConfig& config);

		//Init functions
		void initVariables();
	

		//Prints
#ifdef IS_RATCHET_DEBUG
		void printSpriteColliderPositionPlayer();
#endif

		//Setters
		void setBoolEvent(bool isEv);

		void handleEvent(sf::Event& event);

		void setPlayerByColliderPos();

		//Modifiers
		void setPosition(const float x, const float y);

		//Update functions
		void update() override;
		void updateMovement() override;
		void updateRotation() override;
		void updatePhysics() override;
		void updateJump() override;
		void updateRunningJump() override;
		void setIsOnGround(bool isGround);
		void updateInput() override;

		//Render

		//Destructor
		~Player() override;

	};
}
