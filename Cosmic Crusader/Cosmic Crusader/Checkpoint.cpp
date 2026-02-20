#include "stdafx.h"
#include "Checkpoint.h"

#include "SceneManager.h"

namespace ratchet
{
	Checkpoint::Checkpoint(const CheckpointConfig& config) : GameObject(config)
	{
		m_objectId = config.m_objectID;

		m_RedFlagPath = config.m_RedFlagPath;
		m_GreenFlagPath = config.m_GreenFlagPath;

		if (!m_greenFlagTexture.loadFromFile(m_GreenFlagPath))
		{
			std::cout << "Green Flag UNLOAD";
		}

		if (!m_redFlagTexture.loadFromFile(m_RedFlagPath))
		{
			std::cout << "Red Flag UNLOAD!";
		}

		m_checkPointOffsetX = config.m_checkPointOffsetX;
		m_checkPointOffsetY = config.m_checkPointOffsetY;

		m_isCheckPointPickked = config.m_isCheckPointPickked;
	}
	Checkpoint::~Checkpoint()
	{

	}

	void Checkpoint::serialise(nlohmann::json& jsonFile)
	{
		if (m_isCheckPointPickked)
		{
			for (auto& prop : jsonFile["properties"])
			{
				auto& propName = prop["name"];
				auto& propValue = prop["value"];

				if (propName == "isCheckPointPicked")
				{
					propValue = m_isCheckPointPickked;
				}
			}
		}
	}

	void Checkpoint::Start()
	{
		m_sprite.setTexture(m_redFlagTexture);
	}
	void Checkpoint::OnSensorEnter(GameObject* obj)
	{
		Player* player = dynamic_cast<Player*>(obj);

		if (player)
		{
			if (!m_isCheckPointPickked)
			{
				player->m_playerCheckPointID = m_objectId;
				player->m_checkPointOffsetX = m_checkPointOffsetX;
				player->m_checkPointOffsetY = m_checkPointOffsetY;
				std::cout << "Player HAS TOUCHED CEHCK POINT"<<std::endl;
				m_isCheckPointPickked = true;

				SceneManager::Get().SaveGame();
			}

		}
	}
	void Checkpoint::OnSensorExit(GameObject* obj)
	{
		Player* player = dynamic_cast<Player*>(obj);

		if (player)
		{
			std::cout << "Player HAS Exit CEHCK POINT"<<std::endl;
		}
	}
}