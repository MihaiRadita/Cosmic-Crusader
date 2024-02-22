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
	//this->animationTimer.restart();

	this->initialTexture = false;
	this->animationTimer.restart();

	if (animFrameImg == nullptr)
	{
		this->animFrameImg = new std::vector<sf::Texture>();
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
}


//Geters
int PlayerIdleAnimation::GetAnimIndex() 
{
	return this->PlayerIdleAnimation::animFrameImg->size();
}

void PlayerIdleAnimation::AddAnimationFrames()
{

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
}

int PlayerIdleAnimation::GetCurrentAnimIndex()
{
	return this->currentFrameIndex;
}

sf::Clock PlayerIdleAnimation::GetPlayerAnimTimer()
{
	return this->animationTimer;
}

std::vector<sf::Texture>* PlayerIdleAnimation::animFrameImg;
