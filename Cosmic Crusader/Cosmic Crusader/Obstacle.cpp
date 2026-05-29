#include "stdafx.h"
#include "Obstacle.h"

#include "SceneManager.h"


ratchet::Obstacle::Obstacle(ObstacleConfig& config) : GameObject(config)
{
	m_damage = config.m_damage;
	m_animationActiveTimePass = config.m_animationActiveTimePass;
	m_isAnimationPlaying = config.m_isAnimationPlaying;
	m_spritePath = config.spriteTexturePath;
	m_frameIndexContinueAnimationFrom = config.m_frameIndexContinueAnimationFrom;
	m_animtionTimeLimit = config.m_animtionTimeLimit;

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
	updateDamage();
}

void ratchet::Obstacle::render(sf::RenderTarget& target)
{
	GameObject::render(target);
	//m_collider->drawColliderCenterBased(target);
}

void ratchet::Obstacle::OnSensorEnter(GameObject* obj)
{
	if (obj == m_target)
	{
		if (m_onSensorStay == false)
		{
			m_onSensorStay = true;
		}

		std::cout << "Player HIT OBSTACLE!" << std::endl;

		if (m_isAnimationPlaying)
		{
			m_target->TakeDamage(m_damage);
		}
	}
}

void ratchet::Obstacle::OnSensorExit(GameObject* obj)
{
	if (m_onSensorStay == true)
	{
		m_onSensorStay = false;
	}
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
		m_obstacleAnimation->resetAnimationFrame(m_sprite);
		
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

void ratchet::Obstacle::Start()
{
	m_obstacleAnimation->m_frameIndexContinueAnimationFrom = m_frameIndexContinueAnimationFrom;
	m_obstacleAnimation->SetAnimTimeLimit(m_animtionTimeLimit);
	PostCosntructFixup();
	SetTarget(m_faction);
}

void ratchet::Obstacle::SetTarget(Faction& faction)
{
	for (auto* obj : s_gameObjects)
	{
		if (obj != this)
		{
			if (faction != Faction::FACTION_UNKNOWN && obj->m_faction != Faction::FACTION_UNKNOWN)
			{
				if (faction != obj->m_faction)
				{
					auto* player = dynamic_cast<Player*>(obj);
					if (player)
					{
						m_target = (Creature*)obj;
						break;
					}

				}
			}
		}
	}
}

void ratchet::Obstacle::updateDamage()
{
	if (!m_onSensorStay)
		return;

	if (!m_isAnimationPlaying)
		return;

	m_target->TakeDamage(m_damage);
}
