#pragma once

#include "Creature.h"

namespace ratchet
{
	class SelfControlledCreature : public Creature
	{
	public: 

		SelfControlledCreature(const SelfControlledCreatureConfig& config);

		~SelfControlledCreature() override;

		//The creature target our AI creature will detect and chase
		Creature* m_target;

		//target detect distance 
		float m_targetMaxDistanceDetectionX;
		float m_targetMaxDistanceDetectionY;

		//target lose distance
		float m_targetMaxDistanceLoseX;
		float m_targetMaxDistanceLoseY;

		//target attack distance
		float m_targetMaxDistanceAttackX;
		float m_targetMaxDistanceAttackY;

		//AI Checks
		bool m_isAttacking = false;
		bool m_canJumpOver = false;
		bool m_isFallingRisk = false;

		float m_flySpeed = 0.0f;

		float m_minFollowHeightOffset = 3.0f;

		std::vector<sf::Vector2f> m_targetPointsFollow;

		int m_targetCurrentIndex;
		int m_currentTargetPointIndex = 0;

		EnemyType m_enemyType;

		bool m_canSeePlayerCenter = false;
		bool m_canSeeRightSide = false;
		bool m_canSeeLeftSide = false;


		//Check Attack Target Function
		void checkTargetToAttack(Creature* target);

		void handleSelfCreatureEvent();
		
		void Die() override;

		bool m_isTargetDetected = false;
		bool m_isTagetBehindCharacter = false;
		bool m_isTargetUppperOfCharacter = false;

		bool m_waitTostartAttack = false;


		float m_maxHeightAbovePlayer = 0.5f;
		std::string m_objectLayerName;

		void canJumpOver();
		void isFallingRisk();

		//Setter
		void SetTarget(Faction& faction);

		void PostCosntructFixup() override;


		void computeAimBulletRotation() override;

		void RestartObjectFeatures()override;

		void Start() override;

		//update functions
		void handleEvent();
		void update() override;
	
		void updateMovement() override;

		void render(sf::RenderTarget& target) override;

		//Detect target function
		void detectTarget(Creature* target);

	private:
	};
}

