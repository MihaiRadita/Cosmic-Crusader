#pragma once

#include "GameObjectConfig.h"

namespace ratchet
{
	struct CheckpointConfig : public GameObjectConfig
	{
	
		CheckpointConfig();

		~CheckpointConfig();

		std::string m_RedFlagPath;
		std::string m_GreenFlagPath;

		float m_checkPointOffsetX;
		float m_checkPointOffsetY;

		bool m_isCheckPointPickked;


		virtual bool deserialise(const nlohmann::json& jsonFile) override;
	};
}

