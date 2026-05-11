#pragma once

#include "GameObjectConfig.h"

namespace ratchet
{
	enum class BulletType{None =0, Hit, Explosive};

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

		float m_explosionPositionOffset;

		std::string m_configLayer;

		BulletType m_bulletType;
		std::string m_bulletExplosionPath;

	private:
	};
}


