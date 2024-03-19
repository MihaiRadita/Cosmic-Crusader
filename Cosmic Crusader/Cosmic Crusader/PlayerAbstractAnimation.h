#pragma once
class PlayerAbstractAnimation
{
public:
	virtual void PlayAnimation(sf::Sprite& sprite);
	virtual int GetAnimSize();
	virtual int GetCurrentAnimIndex();
	virtual sf::Clock GetPlayerAnimTimer();
	virtual void ResetCurrentAnimIndex();
	virtual void ResetPlayerAnimTimer();
	virtual bool GetAnimationSwitch();
	virtual void SetAnimationSwitch(bool animSwitch);
	virtual bool IsCurrentAnimationIndexValue();
};

