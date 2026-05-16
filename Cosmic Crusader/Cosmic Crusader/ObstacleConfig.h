#pragma once

#include "GameObjectConfig.h"

namespace ratchet
{
	struct ObstacleConfig : public GameObjectConfig
	{
		ObstacleConfig();

		virtual bool serialise(nlohmann::json& jsonFile) override;
		virtual bool deserialise(const nlohmann::json& jsonFile) override;

		float m_damage;
		float m_animationActiveTimePass;
		float m_colliderOffsetX;
		float m_colliderOffsetY;
		bool m_isAnimationPlaying;

	};
}


