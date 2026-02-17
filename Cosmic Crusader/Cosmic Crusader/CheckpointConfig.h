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


		virtual bool deserialise(const nlohmann::json& jsonFile) override;
	};
}

