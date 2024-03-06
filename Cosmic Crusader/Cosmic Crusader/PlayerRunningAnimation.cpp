#include "stdafx.h"
#include "PlayerRunningAnimation.h"

PlayerRunningAnimation::PlayerRunningAnimation() : animTimeLimit(0.2f), currentFrameIndex(0), isAnimTransition(true)
{
	this->InitVariables();
	this->AddAnimationFrames();
}


void PlayerRunningAnimation::InitVariables()
{
	//this->animationTimer.restart();

	this->initialTexture = false;
	this->animationTimer.restart();

	if (animFrameImg == nullptr)
	{
		this->animFrameImg = new std::vector<sf::Texture>();
		this->AddAnimationFrames();
	}
}


//Geters
int PlayerRunningAnimation::GetAnimIndex()
{
	return this->PlayerRunningAnimation::animFrameImg->size();
}

void PlayerRunningAnimation::AddAnimationFrames()
{
	bool imageValid = false;
	do
	{
		int imgIndex = PlayerRunningAnimation::animFrameImg->size();
		int strImgIndex = imgIndex + 1;

		// Build string
		std::stringstream ss;
		ss << "Textures/PlayerTextures/Player1Textures/RunTextures/";
		ss << "Run";
		ss << strImgIndex;
		ss << ".png";
		std::string path = ss.str();
		ss.clear();

		// Load Texture
		sf::Texture texture;
		imageValid = texture.loadFromFile(path);
		if (imageValid)
		{
			PlayerRunningAnimation::animFrameImg->push_back(texture);
		}

	} while (imageValid);
}

//Play player animation frames
void PlayerRunningAnimation::PlayAnimation(sf::Sprite& sprite)
{
	if (this->currentFrameIndex == 0)
	{
		if (this->isAnimTransition)
		{
			this->isAnimTransition = false;
			sprite.setTexture((*this->animFrameImg)[currentFrameIndex]);
			std::cout << "PLayer Idle image " << currentFrameIndex << std::endl;

		}
		if (this->animationTimer.getElapsedTime().asSeconds() >= this->animTimeLimit)
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
		if (this->animationTimer.getElapsedTime().asSeconds() >= this->animTimeLimit)
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
PlayerRunningAnimation::~PlayerRunningAnimation()
{
	this->DestroyTextureFrames();
}

void PlayerRunningAnimation::DestroyTextureFrames()
{
	delete this->animFrameImg;
}

void PlayerRunningAnimation::ResetCurrentAnimIndex()
{
	this->currentFrameIndex = 0;
}

void PlayerRunningAnimation::ResetPlayerAnimTimer()
{
	this->animationTimer.restart();
}

int PlayerRunningAnimation::GetCurrentAnimIndex()
{
	return this->currentFrameIndex;
}

std::vector<sf::Texture>* PlayerRunningAnimation::animFrameImg;