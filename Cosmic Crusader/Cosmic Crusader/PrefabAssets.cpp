#include "stdafx.h"
#include "PrefabAssets.h"



namespace ratchet
{
	PrefabAssets& ratchet::PrefabAssets::Get()
	{
		static PrefabAssets instance;
		return instance;
	}

	void PrefabAssets::RegisterGameObjectConfig(int& id,GameObjectConfig* config)
	{
		m_gameObjectConfigs[id] = new GameObjectConfig(*config);
	}

	void PrefabAssets::RegisterCreatureConfig(int& id,CreatureConfig& config)
	{
		m_creatureConfigs[id] = new CreatureConfig(config);
	}

	void PrefabAssets::RegisterWeaponConfig(int& id,WeaponConfig* config)
	{
		m_weaponConfigs[id] = new WeaponConfig(*config);
	}

	void PrefabAssets::RegisterBulletConfig(int& id, BulletConfig* config)
	{
		BulletConfig* copy = new BulletConfig(*config);
		m_colliderConfigs[id] = config->m_colliderConfig;

		copy->m_colliderConfig = m_colliderConfigs[id];

		m_bulletConfigs[id] = copy;
	}

	void PrefabAssets::RegisterUIBarConfig(int& id, UIBarConfig* config)
	{
		UIBarConfig* copy = new UIBarConfig(*config);

		m_UIBarConfigs[id] = copy;
	}

	void PrefabAssets::RegisterUIFractionTextConfig(int& id, UIFractionTextConfig* config)
	{
		UIFractionTextConfig* copy = new UIFractionTextConfig(*config);

		m_UIFractionTextConfigs[id] = copy;
	}


	bool PrefabAssets::isCreatureConfigExists(int& id)
	{
		auto it = m_creatureConfigs.find(id);

		if (it != m_creatureConfigs.end())
		{
			return true;
		}

		return false;
	}

	bool PrefabAssets::isWeaponConfigExists(int& id)
	{
		auto it = m_weaponConfigs.find(id);

		if (it != m_weaponConfigs.end())
		{
			return true;
		}

		return false;
	}

	bool PrefabAssets::isGameObjectConfigExists(int& id)
	{
		auto it = m_gameObjectConfigs.find(id);

		if (it != m_gameObjectConfigs.end())
		{
			return true;
		}

		return false;
	}

	bool PrefabAssets::isBulletConfigExists(int& id)
	{
		auto it = m_bulletConfigs.find(id);

		if (it != m_bulletConfigs.end())
		{
			return true;
		}

		return false;
	}

	bool PrefabAssets::isUIBarConfigExists(int& id)
	{
		auto it = m_UIBarConfigs.find(id);

		if (it != m_UIBarConfigs.end())
		{
			return true;
		}


		return false;
	}

	bool PrefabAssets::isUIFractionTextConfigExists(int& id)
	{

		auto it = m_UIFractionTextConfigs.find(id);

		if (it != m_UIFractionTextConfigs.end())
		{
			return true;
		}

		return false;
	}



	GameObjectConfig* PrefabAssets::GetGameObjectConfig(const int& id)
	{
		auto it = m_gameObjectConfigs.find(id);
		if (it != m_gameObjectConfigs.end())
		{
			return it->second;
		}
		return nullptr;
	}

	CreatureConfig* PrefabAssets::GetCreatureConfig(const int& id)
	{
		auto it = m_creatureConfigs.find(id);
		if (it != m_creatureConfigs.end())
		{
			return it->second;
		}
		return nullptr;
	}

	WeaponConfig* PrefabAssets::GetWeaponConfig(const int& id)
	{
		auto it = m_weaponConfigs.find(id);
		if (it != m_weaponConfigs.end())
		{
			return it->second;
		}
		return nullptr;
	}

	BulletConfig* PrefabAssets::GetBulletConfig(const int& id)
	{
		auto it = m_bulletConfigs.find(id);
		if (it != m_bulletConfigs.end())
		{
			return it->second;
		}
		return nullptr;
	}

	UIBarConfig* PrefabAssets::GetUIBarConfig(const int& id)
	{
		auto it = m_UIBarConfigs.find(id);

		if (it != m_UIBarConfigs.end())
		{
			return it->second;
		}

		return nullptr;
	}

	UIFractionTextConfig* PrefabAssets::GetUIFractionTextConfig(const int& id)
	{
		auto it = m_UIFractionTextConfigs.find(id);

		if (it != m_UIFractionTextConfigs.end())
		{
			return it->second;
		}

		return nullptr;
	}

	void PrefabAssets::DestroyPrefabAssets()
	{
		DestroyPrefabConfigs();
	}

	void PrefabAssets::DestroyPrefabConfigs()
	{
		for(auto& [id, ptr] : m_gameObjectConfigs)
		{
			delete ptr;
		}
		m_gameObjectConfigs.clear();

		for (auto& [id, ptr] : m_creatureConfigs)
		{
			delete ptr;
		}
		m_creatureConfigs.clear();

		for (auto& [id, ptr] : m_weaponConfigs)
		{
			delete ptr;
		}
		m_weaponConfigs.clear();

		for (auto& [id, ptr] : m_bulletConfigs)
		{
			delete ptr;
		}

		m_bulletConfigs.clear();

		for (auto& [id, ptr] : m_colliderConfigs)
		{
			delete ptr;
		}

		for (auto& [id, ptr] : m_UIBarConfigs)
		{
			delete ptr;
		}

		m_colliderConfigs.clear();
	}



}

