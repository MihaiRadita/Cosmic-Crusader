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

		if (player)
		{
			if (m_isActionTriggerInteracting == false)
			{
				SceneManager::Get().m_isViewFollow = false;
				
				player->m_isDeath = true;
					
				m_isActionTriggerInteracting = true;
			}
		}
	}

	void ActionTrigger::OnSensorExit(GameObject* obj)
	{
		auto* player = dynamic_cast<Player*>(obj);

		if (player)
		{
			if (m_isActionTriggerInteracting == true)
			{
				SceneManager::Get().m_gameOver = true;
				SceneManager::Get().m_isViewFollow = true;
				m_isActionTriggerInteracting = false;
			}
		}
	}
	void ActionTrigger::SetTarget()
	{
		for (auto* obj : s_gameObjects)
		{

		}
	}
}
