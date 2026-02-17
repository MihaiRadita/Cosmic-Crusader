#include "stdafx.h"
#include "Checkpoint.h"

namespace ratchet
{
	Checkpoint::Checkpoint(const CheckpointConfig& config) : GameObject(config)
	{
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
	}
	Checkpoint::~Checkpoint()
	{

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
			std::cout << "Player HAS TOUCHED CEHCK POINT"<<std::endl;
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