#pragma once
#include "GameObjectConfig.h"

enum class ItemType{None =0, Health, Ammo, HealthRecharger, AmmoRecharger,Spring};

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
		float m_itemDisableTimePass;
		bool m_isItemAccessible;
		float m_animationTimeLimit;
		float m_springForce;

		bool m_isAnimationPlaying;

		std::string m_objectName;
		
		bool m_isItemInteracting = false;
		bool m_isItemUsed = false;

		std::string m_spriteTextureOnPath = "";
		std::string m_spriteTextureOffPath = "";
	};
}


