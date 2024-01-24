#include "stdafx.h"
#include "Animator.h"

Animator::Animator()
{
	this->abstractAnimation = new AbstractAnimation();
	this->animationTmp = this->abstractAnimation;
}

Animator::~Animator()
{
	if (this->abstractAnimation)
	{
		delete this->animationTmp;
		std::cout << "Pointer deleted" << std::endl;
	}
}

AbstractAnimation* Animator::GetAbstractAnimation()
{
	return this->abstractAnimation;
}

void Animator::SetAnimation(AbstractAnimation* anim)
{
	if (dynamic_cast<IdleAnimation*>(anim))
	{
		this->abstractAnimation = anim;
	}
	else if (dynamic_cast<RunningAnimation*>(anim))
	{
		this->abstractAnimation = anim;
	}
}

void Animator::ResetAnimIndex(int& animationIndex)
{
	animationIndex = 0;
}
void Animator::TickAnimIndex(int& animtionIndex)
{
	animtionIndex++;
}