#pragma once

#include "GameObjectConfig.h"

namespace ratchet
{
	struct BackgroundConfig : public GameObjectConfig
	{
		BackgroundConfig();
		~BackgroundConfig();

		virtual bool serialise(nlohmann::json& jsonFile) override;
		virtual bool deserialise(const nlohmann::json& jsonFile) override;

		int m_backgroundId = -1;
	};

}

