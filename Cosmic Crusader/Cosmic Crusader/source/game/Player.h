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
		float m_curreNAgleDeg = 0.0f;

		//Constructors
		Player(const CreatureConfig& config);

		//Init functions
		void initVariables();

		void PostCosntructFixup() override;

		void Start() override;
	

		//Prints
		void render(sf::RenderTarget& target) override;
#ifdef IS_RATCHET_DEBUG
		void printSpriteColliderPositionPlayer();
#endif

		//Setters
		void setBoolEvent(bool isEv);

		void handleEvent(sf::Event& event);

		void setPlayerByColliderPos();

		//Anlle Functions
		void computeAimAngleState() override;
		void computeAimBulletRotation() override;

		//Update functions
		void update() override;
		void updateMovement() override;
		void updateRotation() override;
		void updateJump() override;
		void updateRunningJump() override;
		void setIsOnGround(bool isGround);

		//Render

		//Destructor
		~Player() override;

	};
}
