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
		TRACE_CHANNEL("ANIMATION", "No index to reset!");
#endif
	}

	void AnimationBase::resetPlayerAnimTimer()
	{
#ifdef IS_RATCHET_DEBUG
		TRACE_CHANNEL("ANIMATION", "No animation timer to reset!");
#endif
	}

	bool AnimationBase::getAnimationSwitch()
	{
		return false;
	}

	void AnimationBase::setAnimationSwitch(bool animSwitch)
	{
#ifdef IS_RATCHET_DEBUG
		TRACE_CHANNEL("ANIMATION", "No Animation Switch to change");
#endif
	}

	bool AnimationBase::isCurrentAnimationIndexValue()
	{
		return false;
	}

	void AnimationBase::invertAnimationFramesList(Weapon::TYPE& weaponused)
	{
#ifdef IS_RATCHET_DEBUG
		TRACE_CHANNEL("ANIMATION", "No animation frmae list to reverse");
#endif
	}

	bool AnimationBase::isAnimationEnd()
	{
		return m_endAnimation;
	}

	void AnimationBase::SetAnimationEnd(bool end)
	{
		m_endAnimation = end;
	}

	void AnimationBase::playAnimation(sf::Sprite& sprite, Weapon::TYPE& weaponUsed, WeaponAnimation::ANGLE& angle, WeaponAnimation::STATE& state)
	{
#ifdef IS_RATCHET_DEBUG
		TRACE_CHANNEL("ANIMATION", "Abstract Animation");
#endif
	}
}