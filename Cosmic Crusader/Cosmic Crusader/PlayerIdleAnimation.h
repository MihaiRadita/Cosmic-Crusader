#pragma once

#include "PlayerAbstractAnimation.h"

class PlayerIdleAnimation: public PlayerAbstractAnimation
{
private:
	const int maxFrameIndex;
	const float animTimeLimit;
	int currentFrameIndex;
	static std::vector<sf::Texture>* animFrameImg;
	static std::vector<std::string>* animFrameLinks;
	sf::Texture currentTexture;
	sf::Clock animationTimer;
	

public:
	void PlayAnimation(sf::Sprite* sprite) override;
	int GetAnimIndex() const override;

	//Constructors
	PlayerIdleAnimation();

	//Destructors
	~PlayerIdleAnimation();

	//Init functions
	void InitVariables();

	//Other functions
	void AddAnimationFrames();
	void DestoryAnimationFrames();
	void DestroyTextureFrames();
};



