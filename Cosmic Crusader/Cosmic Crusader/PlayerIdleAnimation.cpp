#include "stdafx.h"
#include "PlayerIdleAnimation.h"


//Constructor functions
PlayerIdleAnimation::PlayerIdleAnimation() :maxFrameIndex(5), animTimeLimit(0.8f), currentFrameIndex(0)
{
	this->InitVariables();
	this->AddAnimationFrames();
}


void PlayerIdleAnimation::InitVariables()
{
	this->animationTimer.restart();

	this->animFrameLinks = new std::vector<std::string>(maxFrameIndex);

	(*PlayerIdleAnimation::animFrameLinks)[0] = "Textures/PlayerTextures/Player1Textures/IdleTextures/Idle1.png";
	(*PlayerIdleAnimation::animFrameLinks)[1] = "Textures/PlayerTextures/Player1Textures/IdleTextures/Idle2.png";
	(*PlayerIdleAnimation::animFrameLinks)[2] = "Textures/PlayerTextures/Player1Textures/IdleTextures/Idle3.png";
	(*PlayerIdleAnimation::animFrameLinks)[3] = "Textures/PlayerTextures/Player1Textures/IdleTextures/Idle4.png";
	(*PlayerIdleAnimation::animFrameLinks)[4] = "Textures/PlayerTextures/Player1Textures/IdleTextures/Idle5.png";

	this->animFrameImg = new std::vector<sf::Texture>(maxFrameIndex);

	for (int i = 0; i < maxFrameIndex; i++)
	{
		(*PlayerIdleAnimation::animFrameImg)[i].loadFromFile((*this->animFrameLinks)[i]);
	}

}


//Geters
int PlayerIdleAnimation::GetAnimIndex() const
{
	return this->maxFrameIndex;
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
	else if (this->currentFrameIndex < this->maxFrameIndex)
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
	this->DestoryAnimationFrames();
	this->DestroyTextureFrames();
}
void PlayerIdleAnimation::DestoryAnimationFrames()
{
	delete this->animFrameLinks;
}

void PlayerIdleAnimation::DestroyTextureFrames()
{
	delete this->animFrameImg;
}

std::vector<std::string>* PlayerIdleAnimation::animFrameLinks;
std::vector<sf::Texture>* PlayerIdleAnimation::animFrameImg;
