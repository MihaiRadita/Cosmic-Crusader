#include "stdafx.h"
#include "PlayerAbstractAnimation.h"

int PlayerAbstractAnimation::GetAnimIndex()
{
	return 0;
}

int PlayerAbstractAnimation::GetCurrentAnimIndex()
{
	return 0;
}

sf::Clock PlayerAbstractAnimation::GetPlayerAnimTimer()
{
	return sf::Clock();
}

void PlayerAbstractAnimation::ResetCurrentAnimIndex()
{
	std::cout << "No index to reset!" << std::endl;
}

void PlayerAbstractAnimation::ResetPlayerAnimTimer()
{
	std::cout << "No animation timer to reset!" << std::endl;
}

void PlayerAbstractAnimation::PlayAnimation(sf::Sprite& sprite)
{
	std::cout << "Abstract Animation";
}