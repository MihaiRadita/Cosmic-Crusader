#pragma once

#include "GameObjectConfig.h"
#include "CreatureConfig.h"
#include "SelfControlledCreatureConfig.h"
#include "WeaponConfig.h"
#include "BulletConfig.h"
#include "TileConfig.h"
#include "physics/RectAngleCollider.h"
#include "UIButtonConfig.h"


namespace ratchet
{
	class PrefabAssets
	{
	public:

		
		static PrefabAssets& Get();

		//List of prefab configs
		std::map<int, GameObjectConfig*> m_gameObjectConfigs;
		std::map<std::string, CreatureConfig*> m_creatureConfigs;
		std::map<int, WeaponConfig*> m_weaponConfigs;
		std::map<int, BulletConfig*> m_bulletConfigs;

		//List of collder prefab configs
		std::map<int, ColliderBaseConfig*> m_colliderConfigs;

		//Registers Config
		void RegisterGameObjectConfig(int& id,GameObjectConfig* config);
		void RegisterCreatureConfig(std::string &id,CreatureConfig& config);
		void RegisterWeaponConfig(int& id,WeaponConfig* config);
		void RegisterBulletConfig(int& id,BulletConfig* config);

		//Getters Configs
		GameObjectConfig* GetGameObjectConfig(const int& id);
		CreatureConfig* GetCreatureConfig(const std::string& id);
		WeaponConfig* GetWeaponConfig(const int& id);
		BulletConfig* GetBulletConfig(const int& id);

		//Destrucotrs
		void DestroyPrefabAssets();
		void DestroyPrefabConfigs();

	private:
	};
}

