#pragma once
class PlayerAbstractAnimation
{
public:
	virtual void playAnimation(sf::Sprite& sprite);
	virtual int getAnimSize();
	virtual int getCurrentAnimIndex();
	virtual sf::Clock getPlayerAnimTimer();
	virtual void resetCurrentAnimIndex();
	virtual void resetPlayerAnimTimer();
	virtual bool getAnimationSwitch();
	virtual void setAnimationSwitch(bool animSwitch);
	virtual bool isCurrentAnimationIndexValue();
};

