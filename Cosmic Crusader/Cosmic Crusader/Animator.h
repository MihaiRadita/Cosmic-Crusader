#pragma once

#include "PlayerAbstractAnimation.h"
#include "PlayerIdleAnimation.h"
#include "PlayerRunningAnimation.h"
#include "PlayerJumpRunningAnimation.h"

class Animator
{
private:
	PlayerAbstractAnimation* m_abstractAnimation;
	PlayerAbstractAnimation* m_animationTmp;

public:
	//Constructor
	Animator();

	//Destructor
	~Animator();


	//Geters
	PlayerAbstractAnimation* getAbstractAnimation();

	//Setters
	void setAnimation(PlayerAbstractAnimation* anim);

	//Play Animation
	void play(PlayerAbstractAnimation* playAnim, sf::Sprite& sprite);

	//Other functions
	void resetAnimIndex(PlayerAbstractAnimation* anim);
	void resetAnimationTimer(PlayerAbstractAnimation* anim);
	void tickAnimIndex(int& animationIndex);
	bool checkCurrentAnimIndex(PlayerAbstractAnimation* anim);
};