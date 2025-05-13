#pragma once

#include "animations/AnimationBase.h"

namespace ratchet
{
	class AnimationIdle : public AnimationBase
	{
	public:
		void playAnimation(sf::Sprite& sprite, Weapon::TYPE& weaponUsed, WeaponAnimation::ANGLE& angle, WeaponAnimation::STATE& state) override;

		//Constructors
		AnimationIdle(std::string& texturePath, std::vector<Weapon::TYPE>& usableWeaponTypeList);

		//Destructors
		~AnimationIdle();

		//Init functions
		void initVariables() override;


		//Other functions
		std::vector<sf::Texture> addAnimationFrames(std::string& texturePath, Weapon::TYPE weaponType, const char* aimingAngle, const char* state) override;
		void resetCurrentAnimIndex() override;
		void resetPlayerAnimTimer() override;
		void setAnimationSwitch(bool animSwitch) override;
		void invertAnimationFramesList(Weapon::TYPE& weaponused) override;

		//Geters Functions	
		int getAnimSize(Weapon::TYPE& type, WeaponAnimation::ANGLE& angle, WeaponAnimation::STATE& state) override;
		int getCurrentAnimIndex() override;
		bool getAnimationSwitch() override;

	private:
		// m_animationFrames[13]; // doar de idle fara arma
		// m_weaponAnimationFramesMap[Weapon::TYPE::BLASTER][Weapon::ANGLE::ANGLE45][Weapon::STATE::AIM][13]; // toate armele
		std::map<Weapon::TYPE, std::map<WeaponAnimation::ANGLE, std::map<WeaponAnimation::STATE, std::vector<sf::Texture>>>> m_weaponAnimationFramesMap; // sa fie redenumit in m_weaponAnimationFramesMap
		std::vector<sf::Texture> m_animationFrames;
	};
}