#include "stdafx.h"
#include "IdleAnimation.h"

void IdleAnimation::PlayAnimation()
{
}

IdleAnimation::IdleAnimation():frameIndex(5)
{
	this->InitVariables();
	this->AddAnimationFrames();
}

IdleAnimation::~IdleAnimation()
{
	
}

void IdleAnimation::InitVariables()
{

	this->animFrameLinks = new std::vector<std::string>(frameIndex);

	(*this->animFrameLinks)[0] = "Textures/PlayerTextures/Player1Textures/IdleTextures/Idle1.png";
	(*this->animFrameLinks)[1] = "Textures/PlayerTextures/Player1Textures/IdleTextures/Idle2.png";
	(*this->animFrameLinks)[2] = "Textures/PlayerTextures/Player1Textures/IdleTextures/Idle3.png";
	(*this->animFrameLinks)[3] = "Textures/PlayerTextures/Player1Textures/IdleTextures/Idle4.png";
	(*this->animFrameLinks)[4] = "Textures/PlayerTextures/Player1Textures/IdleTextures/Idle5.png";

	this->animFrameImg = new std::vector<sf::Texture>(frameIndex);
	
	for (int i = 0; i < frameIndex; i++)
	{
		(*this->animFrameImg)[i].loadFromFile((*this->animFrameLinks)[i]);
	}
	
}

void IdleAnimation::AddAnimationFrames()
{
	
}

void IdleAnimation::DestoryAnimationFrames()
{
	delete this->animFrameLinks;
}

void IdleAnimation::DestroyTextureFrames()
{
	delete this->animFrameImg;
}
