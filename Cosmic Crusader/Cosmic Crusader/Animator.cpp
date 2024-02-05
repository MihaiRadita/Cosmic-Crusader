#include "stdafx.h"
#include "Animator.h"

Animator::Animator()
{
	this->abstractAnimation = new PlayerAbstractAnimation();
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

PlayerAbstractAnimation* Animator::GetAbstractAnimation()
{
	return this->abstractAnimation;
}

void Animator::SetAnimation(PlayerAbstractAnimation* anim)
{
	if (dynamic_cast<PlayerIdleAnimation*>(anim))
	{
		this->abstractAnimation = anim;
	}
	else if (dynamic_cast<PlayerRunningAnimation*>(anim))
	{
		this->abstractAnimation = anim;
	}
}

void Animator::Play(PlayerAbstractAnimation* anim, sf::Sprite& sprite)
{
	anim->PlayAnimation(&sprite);
}



void Animator::ResetAnimIndex(int& animationIndex)
{
	animationIndex = 0;
}
void Animator::TickAnimIndex(int& animtionIndex)
{
	animtionIndex++;
}