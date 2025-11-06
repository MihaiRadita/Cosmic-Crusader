#pragma once

#include "Weapon.h"

namespace ratchet
{
	enum ANIMATION_STATE { 
		IDLE= 0, 
		MOVING,
		JUMP, 
		JUMP_RUNNING,
		FALL,
		Count
	};

	enum class AimingAngle {
		AimingAngle0,
		AimingAngle45,
		AimingAngle90,
		AimingAngleMinus45
	};

	enum class ShootingAngle {
		ShootingAngle0,
		ShootingAngle45,
		ShootingAngle90,
		ShootingAngleMinus45
	};

	class AnimationBase
	{
	public:

		virtual void initVariables();

		//Other functions
		virtual std::vector<sf::Texture> addAnimationFrames(std::string& texturePath, Weapon::TYPE weaponType, const char* aimingAngle, const char* state);

		virtual void playAnimation(sf::Sprite& sprite, Weapon::TYPE& weaponUsed, WeaponAnimation::ANGLE& angle, WeaponAnimation::STATE& state);
		virtual int getAnimSize(Weapon::TYPE& type, WeaponAnimation::ANGLE& angle, WeaponAnimation::STATE& state);
		virtual int getCurrentAnimIndex();
		virtual void resetCurrentAnimIndex();
		virtual void resetPlayerAnimTimer();
		virtual bool getAnimationSwitch();
		virtual void setAnimationSwitch(bool animSwitch);
		virtual bool isCurrentAnimationIndexValue();
		virtual void invertAnimationFramesList(Weapon::TYPE& weaponused);

	protected:
		float m_animTimeLimit;
		int m_currentFrameIndex;
		bool m_isAnimTransition;
		bool m_animationSwitch;
		sf::Clock m_animationTimer;
		bool m_initialTexture;
		bool m_repeatAnimation;
	};
}