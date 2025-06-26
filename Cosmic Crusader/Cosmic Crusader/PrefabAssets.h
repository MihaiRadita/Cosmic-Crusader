#pragma once

#include "GameObjectConfig.h"
#include "CreatureConfig.h"
#include "WeaponConfig.h"
#include "BulletConfig.h"

namespace ratchet
{
	class PrefabAssets
	{
	public:


		static PrefabAssets& Get();

		//List of prefab configs
		std::map<std::string, GameObjectConfig*> m_gameObjectConfigs;
		std::map<std::string, CreatureConfig*> m_creatureConfigs;
		std::map<std::string, WeaponConfig*> m_weaponConfigs;
		std::map<std::string, BulletConfig*> m_bulletConfigs;

		//Registers Config
		void RegisterGameObjectConfig(std::string& id,GameObjectConfig& config);
		void RegisterCreatureConfig(std::string &id,CreatureConfig& config);
		void RegisterWeaponConfig(std::string& id,WeaponConfig& config);
		void RegisterBulletConfig(std::string& id,BulletConfig& config);

		//Getters Configs
		GameObjectConfig* GetGameObjectConfig(std::string& id);
		CreatureConfig* GetCreatureConfig(std::string& id);
		WeaponConfig* GetWeaponConfig(std::string& id);
		BulletConfig* GetBulletConfig(std::string& id);

		//Destrucotrs
		void DestroyPrefabAssets();
		void DestroyPrefabConfigs();

	private:
	};
}

