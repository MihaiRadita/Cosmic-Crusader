#pragma once

#include "animations/AnimationBase.h"

namespace ratchet
{
	class AnimationJump : public AnimationBase
	{
	public:
		void playAnimation(sf::Sprite& sprite, Weapon::TYPE& weaponUsed, WeaponAnimation::ANGLE& angle, WeaponAnimation::STATE& state) override;

		//Constructors
		AnimationJump(std::string& texturePath, std::vector<Weapon::TYPE>& usableWeaponTypeList);

		//Destructor
		~AnimationJump();

		//Init functions
		void initVariables() override;

		//Other functions
		std::vector<sf::Texture> addAnimationFrames(std::string& texturePath, Weapon::TYPE weaponType, const char* aimingAngle, const char* state) override;
		void resetCurrentAnimIndex() override;
		void resetPlayerAnimTimer() override;
		void setAnimationSwitch(bool animSwitch) override;

		//Geters Functions	
		int getAnimSize(Weapon::TYPE& type, WeaponAnimation::ANGLE& angle, WeaponAnimation::STATE& state) override;
		int getCurrentAnimIndex() override;
		bool getAnimationSwitch() override;
		bool isCurrentAnimationIndexValue() override;

	private:
		float m_animTimeJumpLimit;
		int m_jumpAnimFrameIndex;
		float m_currentJumpTimeLimit;
		// TODO: Foloseste ResourceManager asa cum am vorbit in loc de acest vector static.
		std::map<Weapon::TYPE, std::map<WeaponAnimation::ANGLE, std::map<WeaponAnimation::STATE, std::vector<sf::Texture>>>> m_weaponAnimationFramesMap; // sa fie redenumit in m_weaponAnimationFramesMap
		std::vector<sf::Texture> m_animationFrames;
	};
}
