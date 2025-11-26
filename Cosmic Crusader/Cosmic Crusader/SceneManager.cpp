#include "stdafx.h"
#include "SceneManager.h"


namespace ratchet
{
	ratchet::SceneManager::SceneManager()
	{
		CheckAndBuildScenes();
		LoadCombinedScenes();

		m_currentScene = SceneType::MainMenu;


		LoadSceneGameObjects();

	}

	ratchet::SceneManager::~SceneManager()
	{
		if (m_sceneManager != nullptr)
		{
			delete m_sceneManager;
			m_sceneManager = nullptr;
		}
	}

	void ratchet::SceneManager::CheckAndBuildScenes()
	{
		m_baseScenePath = "F:/Users/mihai/Documents/GitHub/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/Levels/Scenes";

		const std::string combinedPath = m_baseScenePath + "GameScenes.json";


		m_sceneFiles = {
			{SceneType::MainMenu, "MainMenu.tmj"},
			{SceneType::Level1, "Level1.tmj"}
		};


		bool needsRebuild = false;

		if (!fs::exists(combinedPath))
		{
			std::cout << "The file with al scenes data needs to be built!" << std::endl;

			needsRebuild = true;
		}
		else
		{
			auto combinedTime = fs::last_write_time(combinedPath);

			for (auto& [type, fileName] : m_sceneFiles)
			{
				fs::path scenePath = m_baseScenePath + fileName;

				if (!fs::exists(scenePath))
				{
					std::cout << "This file of scene does not exist!" << std::endl;
					continue;
				}

				if (fs::last_write_time(scenePath) > combinedTime)
				{
					std::cout << "File scene needs to rebuild!" << std::endl;
					needsRebuild = true;
				}
			}
		}

		if (!needsRebuild)
		{
			return;
		}

		nlohmann::json combined;
		combined["scenes"] = {};

		for (auto& [type, fileName] : m_sceneFiles)
		{
			fs::path fullPath = m_baseScenePath + fileName;

			std::ifstream in(fullPath);

			if (!in.is_open())
			{
				std::cout << "ERROR! The file can not open!" << std::endl;
				continue;
			}

			nlohmann::json sceneJson;

			in >> sceneJson;

			combined["scenes"][fileName] = sceneJson;
		}

		//Cream fisierul final
		std::ofstream out(combinedPath);

		out << std::setw(4) << combined;

		std::cout << "The combined scenes file has been created/updated!" << std::endl;
	}

	void ratchet::SceneManager::LoadCombinedScenes()
	{
		std::string combinedPath = m_baseScenePath + "GameScenes.json";

		if (!fs::exists(combinedPath))
		{
			std::cout << "ERROR! File does not exists!" << std::endl;
			return;
		}

		std::ifstream in(combinedPath);

		in >> m_allScenes;

		std::cout << "The Scene File has been created with scuccess!" << std::endl;

	}

	void SceneManager::updateSceneObjects()
	{
		if (m_currentScene == SceneType::MainMenu)
		{
			m_currentGameSceneState = SceneGameState::Pause;
		}

		const bool updatingUI = (m_currentGameSceneState == SceneGameState::Pause);
		const bool updatingWorld = (m_currentGameSceneState == SceneGameState::Playing);

		for (auto& obj : GameObject::s_gameObjects)
		{
			if ((updatingUI && obj->m_objectType == ObjectType::UI) ||
				(updatingWorld && obj->m_objectType == ObjectType::World))
			{
				obj->update();
			}
		}
	}

	void SceneManager::renderSceneObjects(sf::RenderTarget& target)
	{
		const bool inPause = (m_currentGameSceneState == SceneGameState::Pause);

		for (auto& obj : GameObject::s_gameObjects)
		{
			if (obj->m_objectType == ObjectType::World)
				obj->render(target); 

			if (inPause && obj->m_objectType == ObjectType::UI)
				obj->render(target);
		}
	}

	void SceneManager::LoadScene(SceneType scene)
	{
		if (m_currentScene != scene)
		{
			m_currentScene = scene;
		}

		ClearSceneObjects();

		if (m_currentScene != SceneType::MainMenu)
		{
			m_currentGameSceneState = SceneGameState::Playing;
		}
		else
		{
			m_currentGameSceneState = SceneGameState::Pause;
		}

		LoadSceneGameObjects();
	}

	void SceneManager::LoadNextScene()
	{
		IncreaseSceneIndex();
		m_currentScene = static_cast<SceneType>(m_sceneIndex);

		ClearSceneObjects();

		if (m_currentScene != SceneType::MainMenu)
		{
			m_currentGameSceneState = SceneGameState::Playing;
		}
		else
		{
			m_currentGameSceneState = SceneGameState::Pause;
		}

		LoadSceneGameObjects();
	}

	void SceneManager::IncreaseSceneIndex()
	{
		m_sceneIndex++;

		if (m_sceneIndex >= m_sceneFiles.size())
		{
			m_sceneIndex = 0;
		}
	}

	void SceneManager::LoadSceneGameObjects()
	{
		std::string sceneName = m_sceneFiles[m_currentScene];

		if (!m_allScenes.contains("Scenes")) {
			std::cout << "ERROR: GameScenes.json does not contain 'Scenes' key\n";
			return;
		}

		auto& scenesNode = m_allScenes["Scenes"];
		if (!scenesNode.contains(sceneName)) {
			std::cout << "ERROR: Scene not found in GameScenes.json: " << sceneName << "\n";
			return;
		}
		
		auto& sceneJson = scenesNode[sceneName];

		if (!sceneJson.contains("layers") || !sceneJson["layers"].is_array()) {
			std::cout << "WARNING: Scene has no layers or layers is not an array: " << sceneName << "\n";
			return;
		}

		for (const auto& layer : sceneJson["layers"])
		{
			const auto& validLayer = layer.contains("objects");
			if (!validLayer) continue;

			const auto& layerName = layer["name"].get<std::string>();
			for (const auto& obj : layer["objects"])
			{
				bool succeeded = false;
				if (layerName == "Tile Objects")
				{
					auto config = TileConfig();
					if (config.deserialise(obj))
					{
						GameObject::s_gameObjects.push_back(new Tile(config));
						succeeded = true;
					}
				}
				else if (layerName == "Player")
				{
					auto config = CreatureConfig();
#ifdef IS_RATCHET_DEBUG
					config.m_debugDraw = true;
#endif
					if (config.deserialise(obj))
					{
#ifdef IS_RATCHET_DEBUG
						config.m_colliderConfig->m_debugDraw = false;
#endif
						GameObject::s_gameObjects.push_back(new Player(config));
						succeeded = true;
					}
				}
				else if (layerName == "Enemies")
				{
					auto config = SelfControlledCreatureConfig();
#ifdef IS_RATCHET_DEBUG
					config.m_debugDraw = true;
#endif
					if (config.deserialise(obj))
					{
#ifdef IS_RATCHET_DEBUG
						config.m_colliderConfig->m_debugDraw = false;
#endif
						GameObject::s_gameObjects.push_back(new SelfControlledCreature(config));
						succeeded = true;
					}
				}
				else if (layerName == "Weapons Bullets")
				{
					auto config = BulletConfig();
					if (config.deserialise(obj))
					{
						PrefabAssets::Get().RegisterBulletConfig(config.m_objectID, &config);
						succeeded = true;
					}
				}
				else if (layerName == "Weapons")
				{
					auto config = WeaponConfig(0.0f, 0.0f, true);
					if (config.deserialise(obj))
					{
						if (obj["type"] == "Weapon Pickup")
						{
							GameObject::s_gameObjects.push_back(new WeaponPickup(config));
						}

						PrefabAssets::Get().RegisterWeaponConfig(config.m_objectID, &config);
						succeeded = true;
					}
				}

				if (!succeeded)
				{
					TRACE_CHANNEL("GAMEOBJECT_INIT", "FAILED to deserialise tile.");
				}
			}
		}
	}

	void SceneManager::ClearSceneObjects()
	{
		for (auto& obj : GameObject::s_gameObjects)
		{
			delete obj;
			obj = nullptr;
		}

		GameObject::s_gameObjects.clear();
	}

	SceneManager* ratchet::SceneManager::GetSceneManager()
	{
		if (!m_sceneManager)
		{
			m_sceneManager = new SceneManager();
		}

		return m_sceneManager;
	}

	nlohmann::json& ratchet::SceneManager::GetScene(SceneType type)
	{
		std::string fileName = m_sceneFiles[type];

		return m_allScenes["scenes"][fileName];
	}

	SceneManager* SceneManager::m_sceneManager = nullptr;
}

