#include "stdafx.h"
#include "PlayerJumpRunningAnimation.h"

PlayerJumpRunningAnimation::PlayerJumpRunningAnimation() : animTimeLimit(0.011f), currentFrameIndex(0), animTimeJumpLimit(0.015), jumpAnimFrameIndex(17), isAnimTransition(true)
{
	this->InitVariables();
	this->AddAnimationFrames();
}


void PlayerJumpRunningAnimation::InitVariables()
{
	//this->animationTimer.restart();

	this->initialTexture = false;
	this->animationTimer.restart();
	this->animationSwitch = true;
	this->currentJumpTimeLimit = this->animTimeLimit;

	if (animFrameImg == nullptr)
	{
		this->animFrameImg = new std::vector<sf::Texture>();
		this->AddAnimationFrames();
	}
}


//Geters
int PlayerJumpRunningAnimation::GetAnimSize()
{
	return this->PlayerJumpRunningAnimation::animFrameImg->size();
}

void PlayerJumpRunningAnimation::AddAnimationFrames()
{
	bool imageValid = false;
	do
	{
		int imgIndex = PlayerJumpRunningAnimation::animFrameImg->size();
		int strImgIndex = imgIndex + 1;

		// Build string
		std::stringstream ss;
		ss << "Textures/PlayerTextures/Player1Textures/JumpRunningTextures/";
		ss << "JumpRunning";
		ss << strImgIndex;
		ss << ".png";
		std::string path = ss.str();
		ss.clear();

		// Load Texture
		sf::Texture texture;
		imageValid = texture.loadFromFile(path);
		if (imageValid)
		{
			PlayerJumpRunningAnimation::animFrameImg->push_back(texture);
		}

	} while (imageValid);
}

//Play player animation frames
void PlayerJumpRunningAnimation::PlayAnimation(sf::Sprite& sprite)
{
	if (this->currentFrameIndex == 0)
	{
		if (this->isAnimTransition)
		{
			this->isAnimTransition = false;
			sprite.setTexture((*this->animFrameImg)[currentFrameIndex]);
			std::cout << "PLayer Jump image " << currentFrameIndex << std::endl;

		}
		if (this->animationTimer.getElapsedTime().asSeconds() >= this->currentJumpTimeLimit || this->GetAnimationSwitch())
		{
			this->isAnimTransition = true;
			this->currentFrameIndex++;
			this->animationTimer.restart();
		}
	}
	else if (this->currentFrameIndex > 0)
	{


		if (this->currentFrameIndex >= this->GetAnimSize())
		{
			//this->currentFrameIndex = 0;
			return;
		}
		if (this->isAnimTransition)
		{
			this->isAnimTransition = false;
			sprite.setTexture((*this->animFrameImg)[currentFrameIndex]);
			std::cout << "PLayer Jump image " << currentFrameIndex << std::endl;
		}
		if (this->animationTimer.getElapsedTime().asSeconds() >= this->currentJumpTimeLimit || this->GetAnimationSwitch())
		{
			this->isAnimTransition = true;
			this->currentFrameIndex++;

			if (this->currentFrameIndex == this->jumpAnimFrameIndex)
			{
				this->currentJumpTimeLimit = this->animTimeJumpLimit;
			}

			/*if (this->currentFrameIndex >= this->GetAnimIndex())
			{
				this->currentFrameIndex = 0;
			}*/
			this->animationTimer.restart();
		}
	}
}

//Destroy functions
PlayerJumpRunningAnimation::~PlayerJumpRunningAnimation()
{
	this->DestroyTextureFrames();
}

void PlayerJumpRunningAnimation::DestroyTextureFrames()
{
	delete this->animFrameImg;
}

void PlayerJumpRunningAnimation::ResetCurrentAnimIndex()
{
	this->currentFrameIndex = 0;
}

void PlayerJumpRunningAnimation::ResetPlayerAnimTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void PlayerJumpRunningAnimation::SetAnimationSwitch(bool animSwitch)
{
	this->animationSwitch = animationSwitch;
}

int PlayerJumpRunningAnimation::GetCurrentAnimIndex()
{
	return this->currentFrameIndex;
}

bool PlayerJumpRunningAnimation::GetAnimationSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
	{
		this->animationSwitch = false;
	}

	return anim_switch;
}

bool PlayerJumpRunningAnimation::IsCurrentAnimationIndexValue()
{
	if (this->currentFrameIndex == this->jumpAnimFrameIndex)
	{
		return  false;
		std::cout << "image number action " << this->jumpAnimFrameIndex << " happended!" << std::endl;
	}

	return true;
}

std::vector<sf::Texture>* PlayerJumpRunningAnimation::animFrameImg;