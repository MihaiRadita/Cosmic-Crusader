#include "stdafx.h"
#include "ActionTrigger.h"

#include "SceneManager.h"

namespace ratchet
{
	ActionTrigger::ActionTrigger(const ActionTriggerConfig& config) : GameObject(config)
	{
		m_actionTriggerName = config.m_actionTriggerName;
		m_isActionTriggerInteracting = config.m_isActionTriggerInteracting;

		m_objectId = config.m_objectID;
	}
	ActionTrigger::~ActionTrigger()
	{

	}
	void ActionTrigger::update()
	{

	}

	void ActionTrigger::render(sf::RenderTarget& target)
	{
		GameObject::render(target);
	}

	void ActionTrigger::OnCollisionEnter(GameObject* obj)
	{

	}
	void ActionTrigger::OnCollisionExit(GameObject* obj)
	{

	}
	void ActionTrigger::OnSensorEnter(GameObject* obj)
	{
		auto* player = dynamic_cast<Player*>(obj);
		if (!player) return;


		float volume = player->m_deathFallSound.getVolume();

		volume = SceneManager::Get().GetSoundEffectsVolume();

		player->m_deathFallSound.setVolume(volume);

		player->m_deathFallSound.play();
		
		player->m_isDeathFall = true;

		if (m_isObjectInside) return;

		m_isObjectInside = true;

		player->m_fallingTriggerCount++;

		if (player->m_fallingTriggerCount == 1)
		{
			if (!player->m_isDeath)
			{
				player->m_isDeath = true;
				SceneManager::Get().m_isViewFollow = false;
			}
		}
	}

	void ActionTrigger::OnSensorExit(GameObject* obj)
	{
		auto* player = dynamic_cast<Player*>(obj);

		if (!player) return;

		if (!m_isObjectInside) return;

		m_isObjectInside = false;

		player->m_fallingTriggerCount--;

		if (player->m_fallingTriggerCount <= 0)
		{
			player->m_fallingTriggerCount = 0;

			SceneManager::Get().m_gameOver = true;
			SceneManager::Get().m_isViewFollow = true;
		}
	}
}
