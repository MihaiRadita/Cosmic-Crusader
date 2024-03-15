#include "stdafx.h"
#include "PlayerJumpAnimation.h"

PlayerJumpAnimation::PlayerJumpAnimation() : animTimeLimit(0.035f), currentFrameIndex(0), isAnimTransition(true)
{
	this->InitVariables();
	this->AddAnimationFrames();
}


void PlayerJumpAnimation::InitVariables()
{
	//this->animationTimer.restart();

	this->initialTexture = false;
	this->animationTimer.restart();
	this->animationSwitch = true;

	if (animFrameImg == nullptr)
	{
		this->animFrameImg = new std::vector<sf::Texture>();
		this->AddAnimationFrames();
	}
}


//Geters
int PlayerJumpAnimation::GetAnimIndex()
{
	return this->PlayerJumpAnimation::animFrameImg->size();
}

void PlayerJumpAnimation::AddAnimationFrames()
{
	bool imageValid = false;
	do
	{
		int imgIndex = PlayerJumpAnimation::animFrameImg->size();
		int strImgIndex = imgIndex + 1;

		// Build string
		std::stringstream ss;
		ss << "Textures/PlayerTextures/Player1Textures/JumpTextures/";
		ss << "Jump";
		ss << strImgIndex;
		ss << ".png";
		std::string path = ss.str();
		ss.clear();

		// Load Texture
		sf::Texture texture;
		imageValid = texture.loadFromFile(path);
		if (imageValid)
		{
			PlayerJumpAnimation::animFrameImg->push_back(texture);
		}

	} while (imageValid);
}

//Play player animation frames
void PlayerJumpAnimation::PlayAnimation(sf::Sprite& sprite)
{
	if (this->currentFrameIndex == 0)
	{
		if (this->isAnimTransition)
		{
			this->isAnimTransition = false;
			sprite.setTexture((*this->animFrameImg)[currentFrameIndex]);
			std::cout << "PLayer Jump image " << currentFrameIndex << std::endl;

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
			std::cout << "PLayer Jump image " << currentFrameIndex << std::endl;
		}
		if (this->animationTimer.getElapsedTime().asSeconds() >= this->animTimeLimit || this->GetAnimationSwitch())
		{
			this->isAnimTransition = true;
			this->currentFrameIndex++;
			if (this->currentFrameIndex >= this->GetAnimIndex())
			{
				this->currentFrameIndex = 0;
			}
			this->animationTimer.restart();
		}
	}
}

//Destroy functions
PlayerJumpAnimation::~PlayerJumpAnimation()
{
	this->DestroyTextureFrames();
}

void PlayerJumpAnimation::DestroyTextureFrames()
{
	delete this->animFrameImg;
}

void PlayerJumpAnimation::ResetCurrentAnimIndex()
{
	this->currentFrameIndex = 0;
}

void PlayerJumpAnimation::ResetPlayerAnimTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void PlayerJumpAnimation::SetAnimationSwitch(bool animSwitch)
{
	this->animationSwitch = animationSwitch;
}

int PlayerJumpAnimation::GetCurrentAnimIndex()
{
	return this->currentFrameIndex;
}

bool PlayerJumpAnimation::GetAnimationSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
	{
		this->animationSwitch = false;
	}

	return anim_switch;
}

std::vector<sf::Texture>* PlayerJumpAnimation::animFrameImg;