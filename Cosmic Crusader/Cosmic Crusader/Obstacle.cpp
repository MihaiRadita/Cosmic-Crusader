#include "stdafx.h"
#include "Obstacle.h"

#include "SceneManager.h"


ratchet::Obstacle::Obstacle(ObstacleConfig& config) : GameObject(config)
{
	m_damage = config.m_damage;
	m_animationActiveTimePass = config.m_animationActiveTimePass;
	m_isAnimationPlaying = config.m_isAnimationPlaying;
	m_spritePath = config.spriteTexturePath;

	m_obstacleAnimator = new Animator();

	m_obstacleAnimation = new AnimationObstacle(m_spritePath);

	m_obstacleAnimator->setAnimation(m_obstacleAnimation);

	m_animationPlayInterval.Restart();
}

ratchet::Obstacle::~Obstacle()
{
	delete m_obstacleAnimator;
	m_obstacleAnimator = nullptr;
}

void ratchet::Obstacle::update()
{
	updateObstacleAnimations();
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

void ratchet::Obstacle::updateObstacleAnimations()
{
	if (m_isAnimationPlaying)
	{
		m_obstacleAnimator->play(m_obstacleAnimator->getAbstractAnimation(), m_sprite);

		AnimationBase* animation = m_obstacleAnimator->getAbstractAnimation();

		if (m_animationPlayInterval.GetElapsed().asSeconds() >= m_animationActiveTimePass)
		{
			if (m_obstacleAnimation->isAnimationReachedEnd())
			{
				m_isAnimationPlaying = false;
				m_obstacleAnimation->resetPlayerAnimTimer();
				m_obstacleAnimation->resetCurrentAnimIndex();
				m_animationPlayInterval.Restart();
			}
		}
	}
	else
	{
		AnimationBase* animation = m_obstacleAnimator->getAbstractAnimation();
		if (m_animationPlayInterval.GetElapsed().asSeconds() >= m_animationActiveTimePass)
		{
			m_isAnimationPlaying = true;
			m_obstacleAnimation->resetPlayerAnimTimer();
			m_obstacleAnimation->resetCurrentAnimIndex();
			m_animationPlayInterval.Restart();
		}
	}
}
