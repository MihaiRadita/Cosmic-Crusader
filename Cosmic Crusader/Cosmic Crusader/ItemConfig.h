#pragma once
#include "GameObjectConfig.h"

enum class ItemType{None =0, Health, Ammo};

namespace ratchet
{
	struct ItemConfig : public GameObjectConfig
	{
		ItemConfig();

		virtual bool serialise(nlohmann::json& jsonFile) override;
		virtual bool deserialise(const nlohmann::json& jsonFile) override;

		ItemType m_itemType;
		float m_itemContenntValue;
		int m_itemRefferdId;
	};
}


