#pragma once

#include "Creature.h"

namespace ratchet
{
	class SelfControlledCreature : public Creature
	{
	public: 

		SelfControlledCreature(const SelfControlledCreatureConfig& config);

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

		//Check Attack Target Function
		void checkTargetToAttack(Creature* target);

		bool m_isTargetDetected = false;
		bool m_isTagetBehindCharacter = false;

		//Setter
		void SetTarget(Faction& faction);

		//update functions
		void handleEvent();
		void update() override;
		void updateMovement() override;

		//Detect target function
		void detectTarget(Creature* target);

	private:
	};
}

