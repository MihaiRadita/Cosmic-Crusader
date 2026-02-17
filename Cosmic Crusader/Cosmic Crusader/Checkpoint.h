#pragma once

#include "GameObject.h"

#include "CheckpointConfig.h"

#include "game/Player.h"

namespace ratchet
{
	class Checkpoint : public GameObject
	{
	public:

		Checkpoint(const CheckpointConfig& config);
		~Checkpoint();


		sf::Texture m_redFlagTexture;
		sf::Texture m_greenFlagTexture;

		std::string m_RedFlagPath;
		std::string m_GreenFlagPath;

		void Start() override;

		virtual void OnSensorEnter(GameObject* obj) override;
		virtual void OnSensorExit(GameObject* obj) override;

	private:
	};
}

