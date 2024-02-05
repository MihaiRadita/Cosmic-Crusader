#pragma once
class PlayerAbstractAnimation
{
public:
	virtual void PlayAnimation(sf::Sprite* sprite);
	virtual int GetAnimIndex() const;
};

