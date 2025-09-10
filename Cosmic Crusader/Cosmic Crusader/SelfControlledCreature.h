#pragma once

#include "Creature.h"

namespace ratchet
{
	class SelfControlledCreature : public Creature
	{
	public: 

		SelfControlledCreature(const CreatureConfig& config);

		//The creature target our AI creature will detect and chase
		Creature* m_target;

		//target detect distance 
		float m_targetMaxDistanceDetectionX;
		float m_targetMaxDistanceDetectionY;

		//target lose distance
		float m_targetMaxDistanceLoseX;
		float m_targetMaxDistanceLoseY;

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

