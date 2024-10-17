#pragma once
#include "GameObject.h"
#include "CreatureConfig.h"


#include "animations/Animator.h"
#include "animations/AnimationIdle.h"
#include "animations/AnimationRun.h"
#include "animations/AnimationJump.h"
#include "animations/AnimationJumpRun.h"
#include "animations/Animator.h"

namespace ratchet
{
	class Creature : public GameObject
	{
	public:


		//Character Features
		float m_movementSpeed;
		float m_fallingSpeed;
		float m_jumpImpulse;
		bool m_isMoving;

		//Character Animations
		std::map<ANIMATION_STATE, AnimationBase*> m_animationList;
		int m_characterAnimSwitch;
		ANIMATION_STATE m_characterAnimationState;
		std::vector<std::string> animationsTexturesPath;
		Animator* m_characterAnimator;

		//Constructors
		Creature(const CreatureConfig& config);

		//Destructors
		~Creature() override;

		//Update Function
		void update() override;
		void updateInput() override;
		void updateMovement() override;
		void updateRotation() override;
		void updatePhysics() override;
		void updateAnimations();
		void updateJump() override;
		void updateRunningJump() override;

		//Render functions

		//Sprite functions
		void invertCharacterMovingSpriteScale(int direction);
		bool isNoControlActive();

		//Input functions

		//Animation functions
		void switchAnimation();

		// Physics
		bool isGrounded() const { return m_isGround; };

	private:
		bool m_isGround;
	};
}


