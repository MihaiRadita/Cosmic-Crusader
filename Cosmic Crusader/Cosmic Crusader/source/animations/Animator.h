#pragma once

#include "animations/AnimationBase.h"
#include "animations/AnimationIdle.h"
#include "animations/AnimationRun.h"
#include "animations/AnimationJumpRun.h"
#include "Weapon.h"


namespace ratchet
{
	class Animator
	{
	private:
		AnimationBase* m_abstractAnimation;
		AnimationBase* m_animationTmp;

	public:
		//Constructor
		Animator();

		//Destructor
		~Animator();

		//Geters
		AnimationBase* getAbstractAnimation();

		//Setters
		void setAnimation(AnimationBase* anim);

		//Play Animation
		void play(AnimationBase* playAnim, sf::Sprite& sprite, Weapon::TYPE& weaponUsed, WeaponAnimation::ANGLE& angle, WeaponAnimation::STATE& state);

		void invertAnimation(AnimationBase* anim, Weapon::TYPE& weaponUsed);

		//Other functions
		void resetAnimIndex(AnimationBase* anim);
		void resetAnimationTimer(AnimationBase* anim);
		void tickAnimIndex(int& animationIndex);
		bool checkCurrentAnimIndex(AnimationBase* anim);

		void setWeapon(Weapon::TYPE weaponType);


		Weapon::TYPE m_weaponAnimation;
	};
}