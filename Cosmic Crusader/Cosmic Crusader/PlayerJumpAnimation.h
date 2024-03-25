#pragma once

#include "PlayerAbstractAnimation.h"

class PlayerJumpAnimation : public PlayerAbstractAnimation
{
private:
	const float animTimeLimit;
	int currentFrameIndex;
	const float animTimeJumpLimit;
	const int jumpAnimFrameIndex;
	bool isAnimTransition;
	float currentJumpTimeLimit;
	bool animationSwitch;
	static std::vector<sf::Texture>* animFrameImg;
	sf::Clock animationTimer;
	bool initialTexture;

public:
	void PlayAnimation(sf::Sprite& sprite) override;

	//Constructors
	PlayerJumpAnimation();

	//Destructor
	~PlayerJumpAnimation();

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
	bool IsCurrentAnimationIndexValue() override;
};

