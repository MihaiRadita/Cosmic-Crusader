#pragma once

#include "PlayerAbstractAnimation.h"
#include "PlayerIdleAnimation.h"
#include "PlayerRunningAnimation.h"

class Animator
{
private:
	PlayerAbstractAnimation* abstractAnimation;
	PlayerAbstractAnimation* animationTmp;

public:
	//Constructor
	Animator();

	//Destructor
	~Animator();


	//Geters
	PlayerAbstractAnimation* GetAbstractAnimation();

	//Setters
	void SetAnimation(PlayerAbstractAnimation* anim);

	//Play Animation
	void Play(PlayerAbstractAnimation* playAnim, sf::Sprite& sprite);

	//Other functions
	void ResetAnimIndex(int& animationIndex);
	void TickAnimIndex(int& animationIndex);



};