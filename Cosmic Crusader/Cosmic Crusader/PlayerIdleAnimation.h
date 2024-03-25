#pragma once

#include "PlayerAbstractAnimation.h"

class PlayerIdleAnimation: public PlayerAbstractAnimation
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
	PlayerIdleAnimation();

	//Destructors
	~PlayerIdleAnimation();

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
	sf::Clock GetPlayerAnimTimer() override;
};



