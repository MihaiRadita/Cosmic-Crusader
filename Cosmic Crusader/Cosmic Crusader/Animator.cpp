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
	this->abstractAnimation = anim;
}

void Animator::Play(PlayerAbstractAnimation* anim, sf::Sprite& sprite)
{
	anim->PlayAnimation(sprite);
}



void Animator::ResetAnimIndex(PlayerAbstractAnimation* anim)
{
	anim->ResetCurrentAnimIndex();
}

void Animator::TickAnimIndex(int& animtionIndex)
{
	animtionIndex++;
}

bool Animator::CheckCurrentAnimIndex(PlayerAbstractAnimation* anim)
{
	return anim->IsCurrentAnimationIndexValue();
}

void Animator::ResetAnimationTimer(PlayerAbstractAnimation* anim)
{
	this->abstractAnimation->ResetPlayerAnimTimer();
}
