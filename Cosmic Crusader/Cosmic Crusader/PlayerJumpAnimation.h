#pragma once

#include "PlayerAbstractAnimation.h"

class PlayerJumpAnimation : public PlayerAbstractAnimation
{
private:
	const float c_animTimeLimit;
	int m_currentFrameIndex;
	const float c_animTimeJumpLimit;
	const int c_jumpAnimFrameIndex;
	bool m_isAnimTransition;
	float m_currentJumpTimeLimit;
	bool m_animationSwitch;
	static std::vector<sf::Texture>* s_animFrameImg;
	sf::Clock m_animationTimer;
	bool m_initialTexture;

public:
	void playAnimation(sf::Sprite& sprite) override;

	//Constructors
	PlayerJumpAnimation();

	//Destructor
	~PlayerJumpAnimation();

	//Init functions
	void initVariables();

	//Other functions
	void addAnimationFrames();
	void destroyTextureFrames();
	void resetCurrentAnimIndex() override;
	void resetPlayerAnimTimer() override;
	void setAnimationSwitch(bool animSwitch) override;

	//Geters Functions	
	int getAnimSize() override;
	int getCurrentAnimIndex() override;
	bool getAnimationSwitch() override;
	bool isCurrentAnimationIndexValue() override;
};

