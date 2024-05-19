#include "stdafx.h"
#include "PlayerAbstractAnimation.h"

int PlayerAbstractAnimation::getAnimSize()
{
	return 0;
}

int PlayerAbstractAnimation::getCurrentAnimIndex()
{
	return 0;
}

sf::Clock PlayerAbstractAnimation::getPlayerAnimTimer()
{
	return sf::Clock();
}

void PlayerAbstractAnimation::resetCurrentAnimIndex()
{
	std::cout << "No index to reset!" << std::endl;
}

void PlayerAbstractAnimation::resetPlayerAnimTimer()
{
	std::cout << "No animation timer to reset!" << std::endl;
}

bool PlayerAbstractAnimation::getAnimationSwitch()
{
	return false;
}

void PlayerAbstractAnimation::setAnimationSwitch(bool animSwitch)
{
	std::cout << "No Animation Switch to change";
}

bool PlayerAbstractAnimation::isCurrentAnimationIndexValue()
{
	return false;
}

void PlayerAbstractAnimation::playAnimation(sf::Sprite& sprite)
{
	std::cout << "Abstract Animation";
}