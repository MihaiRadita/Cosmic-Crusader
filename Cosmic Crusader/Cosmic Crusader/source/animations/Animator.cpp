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
			std::cout << "Pointer deleted" << std::endl;
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

	void Animator::play(AnimationBase* anim, sf::Sprite& sprite)
	{
		anim->playAnimation(sprite);
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

	void Animator::resetAnimationTimer(AnimationBase* anim)
	{
		m_abstractAnimation->resetPlayerAnimTimer();
	}
}
