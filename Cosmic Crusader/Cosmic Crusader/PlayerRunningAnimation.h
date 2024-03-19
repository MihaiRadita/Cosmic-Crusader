#pragma once

#include "PlayerAbstractAnimation.h"

class PlayerRunningAnimation: public PlayerAbstractAnimation
{
private:
	const float animTimeLimit;
	int currentFrameIndex;
	bool isAnimTransition;
	bool animationSwitch;
	static std::vector<sf::Texture>* animFrameImg;
	sf::Clock animationTimer;
	bool initialTexture;

public:
	void PlayAnimation(sf::Sprite& sprite) override;

	//Constructors
	PlayerRunningAnimation();

	//Destructor
	~PlayerRunningAnimation();

	//Init functions
	void InitVariables();

	//Other functions
	void AddAnimationFrames();
	void DestroyTextureFrames();
	void ResetCurrentAnimIndex() override;
	void ResetPlayerAnimTimer() override;
	void SetAnimationSwitch(bool animSwitch) override;
	//Geters Functions	
	int GetAnimSize() override;
	int GetCurrentAnimIndex() override;
	bool GetAnimationSwitch() override;
};

