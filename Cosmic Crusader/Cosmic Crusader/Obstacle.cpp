#include "stdafx.h"
#include "Obstacle.h"

#include "SceneManager.h"

ratchet::Obstacle::Obstacle(ObstacleConfig& config) : GameObject(config)
{
	m_damage = config.m_damage;
	m_animationActiveTimePass = config.m_animationActiveTimePass;
	m_isAnimationPlaying = config.m_isAnimationPlaying;
}

ratchet::Obstacle::~Obstacle()
{

}

void ratchet::Obstacle::update()
{

}

void ratchet::Obstacle::render(sf::RenderTarget& target)
{
	GameObject::render(target);
	m_collider->drawColliderCenterBased(target);
}

void ratchet::Obstacle::OnSensorEnter(GameObject* obj)
{
 	if (auto* player = dynamic_cast<Player*>(obj))
	{
		std::cout << "Player HIT OBSTACLE!" << std::endl;
	}
}

void ratchet::Obstacle::OnSensorExit(GameObject* obj)
{

}
