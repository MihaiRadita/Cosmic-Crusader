#pragma once

#include "GameObjectConfig.h"

namespace ratchet
{
	enum class ActionTriggerName {
		None =0,
		DeathFalll
	};

	struct ActionTriggerConfig : public GameObjectConfig
	{

		ActionTriggerConfig();
		~ActionTriggerConfig();

		virtual bool serialise(nlohmann::json& jsonFile) override;
		virtual bool deserialise(const nlohmann::json& jsonFile) override;


		ActionTriggerName m_actionTriggerName;

		bool m_isActionTriggerInteracting = false;
		
		float m_triggerShapeSizeX;
		float m_triggerShapeSizeY;

		sf::Color m_triggerShapeColor;
	};

}


