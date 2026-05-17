#include "stdafx.h"
#include "Animator.h"



namespace ratchet
{
	Animator::Animator()
	{
		m_abstractAnimation = new AnimationBase();
		m_animationTmp = m_abstractAnimation;
	}

	Animator::~Animator()
	{
		if (m_abstractAnimation)
		{
			delete m_animationTmp;
#ifdef IS_RATCHET_DEBUG
			TRACE_CHANNEL("ANIMATION", "Pointer deleted");
#endif
		}
	}

	AnimationBase* Animator::getAbstractAnimation()
	{
		return m_abstractAnimation;
	}

	void Animator::setAnimation(AnimationBase* anim)
	{
		m_abstractAnimation = anim;
	}

	void Animator::play(AnimationBase* anim, sf::Sprite& sprite, Weapon::TYPE& weaponUsed, WeaponAnimation::ANGLE& angle, WeaponAnimation::STATE& state)
	{
#ifdef IS_RATCHET_DEBUG
		TRACE_CHANNEL("ANIMATION_SPAM", (std::string("Animation | ") + std::string("Angle: '") + std::to_string(static_cast<int>(angle)) + std::string("', State: '") + std::to_string(static_cast<int>(state)) + std::string("'")).c_str());
#endif
		anim->playAnimation(sprite, weaponUsed, angle, state);
	}

	void Animator::play(AnimationBase* playAnim, sf::Sprite& sprite)
	{
		playAnim->playAnimation(sprite);
	}

	void Animator::invertAnimation(AnimationBase* anim, Weapon::TYPE& weaponUsed)
	{
		anim->invertAnimationFramesList(weaponUsed);
	}

	void Animator::resetAnimIndex(AnimationBase* anim)
	{
		anim->resetCurrentAnimIndex();
	}

	void Animator::tickAnimIndex(int& animtionIndex)
	{
		animtionIndex++;
	}

	bool Animator::checkCurrentAnimIndex(AnimationBase* anim)
	{
		return anim->isCurrentAnimationIndexValue();
	}

	void Animator::setWeapon(Weapon::TYPE weaponType)
	{
		m_weaponAnimation = weaponType;
	}

	void Animator::resetAnimationTimer(AnimationBase* anim)
	{
		m_abstractAnimation->resetPlayerAnimTimer();
	}

}
