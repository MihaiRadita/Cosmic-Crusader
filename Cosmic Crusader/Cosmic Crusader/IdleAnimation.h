#pragma once

#include "AbstractAnimation.h"

class IdleAnimation : public AbstractAnimation
{
private:
	const int frameIndex;
	std::vector<sf::Texture>* animFrameImg;
	std::vector<std::string>* animFrameLinks;

public:
	void PlayAnimation() override;

	//Constructors
	IdleAnimation();

	//Destructors
	~IdleAnimation();

	//Init functions
	void InitVariables();

	//Other functions
	void AddAnimationFrames();
	void DestoryAnimationFrames();
	void DestroyTextureFrames();

};

