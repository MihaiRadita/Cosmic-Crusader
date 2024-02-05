#include "stdafx.h"
#include "PlayerIdleAnimation.h"



//Constructor functions
PlayerIdleAnimation::PlayerIdleAnimation() : animTimeLimit(0.8f), currentFrameIndex(0)
{
	this->InitVariables();
	this->AddAnimationFrames();
}


void PlayerIdleAnimation::InitVariables()
{
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
int PlayerIdleAnimation::GetAnimIndex() const
{
	return this->PlayerIdleAnimation::animFrameImg->size();
}

void PlayerIdleAnimation::AddAnimationFrames()
{

}

//Play player animation frames
void PlayerIdleAnimation::PlayAnimation(sf::Sprite* sprite)
{
	if (currentFrameIndex == 0)
	{
		sprite->setTexture((*this->animFrameImg)[currentFrameIndex]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= this->animTimeLimit)
		{
			this->currentFrameIndex++;
			this->animationTimer.restart();
		}
	}
	else if (this->currentFrameIndex < this->GetAnimIndex())
	{
		sprite->setTexture((*this->animFrameImg)[currentFrameIndex]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= this->animTimeLimit)
		{
			this->currentFrameIndex++;
			this->animationTimer.restart();
		}
	}
	else
	{
		this->currentFrameIndex = 0;
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

std::vector<sf::Texture>* PlayerIdleAnimation::animFrameImg;
