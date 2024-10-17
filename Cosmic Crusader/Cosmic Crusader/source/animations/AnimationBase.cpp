#include "stdafx.h"
#include "AnimationBase.h"

namespace ratchet
{
	void AnimationBase::initVariables()
	{
	}

	void AnimationBase::addAnimationFrames(std::string& texturePath)
	{
	}

	int AnimationBase::getAnimSize()
	{
		return 0;
	}

	int AnimationBase::getCurrentAnimIndex()
	{
		return 0;
	}

	void AnimationBase::resetCurrentAnimIndex()
	{
#ifdef IS_RATCHET_DEBUG
		//std::cout << "No index to reset!" << std::endl;
#endif
	}

	void AnimationBase::resetPlayerAnimTimer()
	{
#ifdef IS_RATCHET_DEBUG
		//std::cout << "No animation timer to reset!" << std::endl;
#endif
	}

	bool AnimationBase::getAnimationSwitch()
	{
		return false;
	}

	void AnimationBase::setAnimationSwitch(bool animSwitch)
	{
#ifdef IS_RATCHET_DEBUG
		//std::cout << "No Animation Switch to change";
#endif
	}

	bool AnimationBase::isCurrentAnimationIndexValue()
	{
		return false;
	}

	void AnimationBase::playAnimation(sf::Sprite& sprite)
	{
#ifdef IS_RATCHET_DEBUG
		//std::cout << "Abstract Animation";
#endif
	}
}