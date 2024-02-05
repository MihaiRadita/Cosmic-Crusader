#include "stdafx.h"
#include "PlayerAbstractAnimation.h"

int PlayerAbstractAnimation::GetAnimIndex() const
{
	return 0;
}

void PlayerAbstractAnimation::PlayAnimation(sf::Sprite* sprite)
{
	std::cout << "Abstract Animation";
}