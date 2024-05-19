#include "stdafx.h"
#include "Animator.h"

Animator::Animator()
{
	this->m_abstractAnimation = new PlayerAbstractAnimation();
	this->m_animationTmp = this->m_abstractAnimation;
}

Animator::~Animator()
{
	if (this->m_abstractAnimation)
	{
		delete this->m_animationTmp;
		std::cout << "Pointer deleted" << std::endl;
	}
}

PlayerAbstractAnimation* Animator::getAbstractAnimation()
{
	return this->m_abstractAnimation;
}

void Animator::setAnimation(PlayerAbstractAnimation* anim)
{
	this->m_abstractAnimation = anim;
}

void Animator::play(PlayerAbstractAnimation* anim, sf::Sprite& sprite)
{
	anim->playAnimation(sprite);
}



void Animator::resetAnimIndex(PlayerAbstractAnimation* anim)
{
	anim->resetCurrentAnimIndex();
}

void Animator::tickAnimIndex(int& animtionIndex)
{
	animtionIndex++;
}

bool Animator::checkCurrentAnimIndex(PlayerAbstractAnimation* anim)
{
	return anim->isCurrentAnimationIndexValue();
}

void Animator::resetAnimationTimer(PlayerAbstractAnimation* anim)
{
	this->m_abstractAnimation->resetPlayerAnimTimer();
}
