#pragma once

#include "AbstractAnimation.h"
#include "IdleAnimation.h"
#include "RunningAnimation.h"

class Animator
{
private:
	AbstractAnimation* abstractAnimation;
	AbstractAnimation* animationTmp;

public:
	//Constructor
	Animator();

	//Destructor
	~Animator();


	//Geters
	AbstractAnimation* GetAbstractAnimation();

	//Setters
	void SetAnimation(AbstractAnimation* anim);

	//Other functions
	void ResetAnimIndex(int &animationIndex);
	void TickAnimIndex(int &animationIndex);



};

