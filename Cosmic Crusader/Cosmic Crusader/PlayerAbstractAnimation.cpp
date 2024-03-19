#include "stdafx.h"
#include "PlayerAbstractAnimation.h"

int PlayerAbstractAnimation::GetAnimSize()
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

bool PlayerAbstractAnimation::GetAnimationSwitch()
{
	return false;
}

void PlayerAbstractAnimation::SetAnimationSwitch(bool animSwitch)
{
	std::cout << "No Animation Switch to change";
}

bool PlayerAbstractAnimation::IsCurrentAnimationIndexValue()
{
	return false;
}

void PlayerAbstractAnimation::PlayAnimation(sf::Sprite& sprite)
{
	std::cout << "Abstract Animation";
}