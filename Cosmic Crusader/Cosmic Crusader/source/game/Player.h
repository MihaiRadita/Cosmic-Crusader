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

		Timer m_timeBeingInvulnerable;

		float m_timeLimitInvulnerable = 1.f;

		bool m_isOnSpring = false;


		std::vector<sf::Event> m_playerEvents;
	public:
		float m_curreNAgleDeg = 0.0f;

		//Constructors
		Player(const CreatureConfig& config);

		Timer GettimeBeingInvulnerable();
		float GetTImeLimitBeingInvulnerable();

		bool getIsOnSpring();

		int m_playerCheckPointID = 0;

		//Init functions
		void initVariables();


		void applyUpforce(b2Vec2 force);

		void Start() override;

		void Die() override;

		void updateTrace() override;

		void updateInvulnerability();
	

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

		void RestartObjectFeatures()override;

		//Update functions
		void update() override;

		void updateMovement() override;
		void updateRotation() override;
		void updateJump() override;
		void updateRunningJump() override;
		void setIsOnGround(bool isGround);

		void serialise(nlohmann::json& jsonFile) override;

		void OnCollisionEnter(GameObject* obj) override;

		//Render

		//Destructor
		~Player() override;

	};
}
