#pragma once

#include "GameObjectConfig.h"

namespace ratchet
{
	class BulletConfig : public GameObjectConfig
	{
	public:

		BulletConfig(); 

		virtual bool serialise(nlohmann::json& jsonFile) override;
		virtual bool deserialise(const nlohmann::json& jsonFile) override;

		float m_damage;
		float m_ammo;

		float m_bulletLifeLimit;

		float m_BulletSpeed;

		std::string m_configLayer;

	private:
	};
}


