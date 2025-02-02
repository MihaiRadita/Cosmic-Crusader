#include "stdafx.h"
#include "AnimationBase.h"

namespace ratchet
{
	void AnimationBase::initVariables()
	{
	}

	std::vector<sf::Texture> AnimationBase::addAnimationFrames(std::string& texturePath, Weapon::TYPE weaponType, const char* aimingAngle, const char* state)
	{
		return std::vector<sf::Texture>();
	}

	int AnimationBase::getAnimSize(Weapon::TYPE& type, WeaponAnimation::ANGLE& angle, WeaponAnimation::STATE& state)
	{
		return 0;
	}

	int AnimationBase::getCurrentAnimIndex()
	{
		return 0;
	}

	void AnimationBase::resetCurrentAnimIndex()
	{
#ifdef IS_RATCHET_DEBUG
		//std::cout << "No index to reset!" << std::endl;
#endif
	}

	void AnimationBase::resetPlayerAnimTimer()
	{
#ifdef IS_RATCHET_DEBUG
		//std::cout << "No animation timer to reset!" << std::endl;
#endif
	}

	bool AnimationBase::getAnimationSwitch()
	{
		return false;
	}

	void AnimationBase::setAnimationSwitch(bool animSwitch)
	{
#ifdef IS_RATCHET_DEBUG
		//std::cout << "No Animation Switch to change";
#endif
	}

	bool AnimationBase::isCurrentAnimationIndexValue()
	{
		return false;
	}

	void AnimationBase::playAnimation(sf::Sprite& sprite, Weapon::TYPE& weaponUsed, WeaponAnimation::ANGLE& angle, WeaponAnimation::STATE& state)
	{
#ifdef IS_RATCHET_DEBUG
		//std::cout << "Abstract Animation";
#endif
	}
}