#pragma once

#include "stdafx.h"
#include "GameObjectConfig.h"

namespace ratchet
{
	struct TileConfig : public GameObjectConfig
	{
		virtual bool serialise(nlohmann::json& jsonFile) override;
		virtual bool deserialise(const nlohmann::json& jsonFile) override;
	};
}

