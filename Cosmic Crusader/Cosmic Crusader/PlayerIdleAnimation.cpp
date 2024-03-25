#include "stdafx.h"
#include "PlayerIdleAnimation.h"



//Constructor functions
PlayerIdleAnimation::PlayerIdleAnimation() : animTimeLimit(0.5f), currentFrameIndex(0), isAnimTransition(true)
{
	this->InitVariables();
	this->AddAnimationFrames();
}

void PlayerIdleAnimation::InitVariables()
{
	this->initialTexture = false;
	this->animationTimer.restart();
	this->animationSwitch = true;

	if (animFrameImg == nullptr)
	{
		this->animFrameImg = new std::vector<sf::Texture>();
		this->AddAnimationFrames();
	}
}

void PlayerIdleAnimation::AddAnimationFrames()
{
	bool imageValid = false;
	do
	{
		int imgIndex = PlayerIdleAnimation::animFrameImg->size();
		int strImgIndex = imgIndex + 1;

		// Build string
		std::stringstream ss;
		ss << "Textures/PlayerTextures/Player1Textures/IdleTextures/";
		ss << "Idle";
		ss << strImgIndex;
		ss << ".png";
		std::string path = ss.str();
		ss.clear();

		// Load Texture
		sf::Texture texture;
		imageValid = texture.loadFromFile(path);
		if (imageValid)
		{
			PlayerIdleAnimation::animFrameImg->push_back(texture);
		}

	} while (imageValid);
}

//Play player animation frames
void PlayerIdleAnimation::PlayAnimation(sf::Sprite& sprite)
{
	if (!this->initialTexture)
	{
		this->currentFrameIndex++;
		this->initialTexture = true;
	}
	if (this->currentFrameIndex == 0)
	{
		if (this->isAnimTransition)
		{
			this->isAnimTransition = false;
			sprite.setTexture((*this->animFrameImg)[currentFrameIndex]);
			std::cout << "PLayer Idle image " << currentFrameIndex<<std::endl;

		}
		if (this->animationTimer.getElapsedTime().asSeconds() >= this->animTimeLimit || this->GetAnimationSwitch())
		{
			this->isAnimTransition = true;
			this->currentFrameIndex++;
			this->animationTimer.restart();
		}
	}
	else if (this->currentFrameIndex > 0)
	{
		if (this->isAnimTransition)
		{
			this->isAnimTransition = false;
			sprite.setTexture((*this->animFrameImg)[currentFrameIndex]);
			std::cout << "PLayer Idle image " << currentFrameIndex << std::endl;
		}
		if (this->animationTimer.getElapsedTime().asSeconds() >= this->animTimeLimit || this->GetAnimationSwitch())
		{
			this->isAnimTransition = true;
			this->currentFrameIndex++;
			if (this->currentFrameIndex >= this->GetAnimSize())
			{
				this->currentFrameIndex = 0;
			}
			this->animationTimer.restart();
		}
	}
}

//Destroy functions
PlayerIdleAnimation::~PlayerIdleAnimation()
{
	this->DestroyTextureFrames();
}

void PlayerIdleAnimation::DestroyTextureFrames()
{
	delete this->animFrameImg;
}

void PlayerIdleAnimation::ResetCurrentAnimIndex()
{
	this->currentFrameIndex = 0;
}

void PlayerIdleAnimation::ResetPlayerAnimTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void PlayerIdleAnimation::SetAnimationSwitch(bool animSwitch)
{
	this->animationSwitch = animSwitch;
}

//Getters Functions
int PlayerIdleAnimation::GetAnimSize() 
{
	return this->PlayerIdleAnimation::animFrameImg->size();
}

int PlayerIdleAnimation::GetCurrentAnimIndex()
{
	return this->currentFrameIndex;
}

bool PlayerIdleAnimation::GetAnimationSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
	{
		this->animationSwitch = false;
	}

	return anim_switch;
}

sf::Clock PlayerIdleAnimation::GetPlayerAnimTimer()
{
	return this->animationTimer;
}

std::vector<sf::Texture>* PlayerIdleAnimation::animFrameImg;
