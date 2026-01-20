#include "stdafx.h"
#include "SceneManager.h"
#include "Weapon.h"

namespace ratchet
{
	ratchet::SceneManager::SceneManager()
	{
		CheckAndBuildScenes();
		LoadCombinedScenes();

		m_currentScene = SceneType::MainMenu;
		m_sceneIndex = static_cast<int>(m_currentScene);
	}

	bool SceneManager::FindObjectById(int& id, nlohmann::json& outObj, const std::string& layerName)
	{
		auto& scene = GetScene(m_currentScene);

		if (!scene.contains("layers") || !scene["layers"].is_array()) {
			std::cout << "WARNING: Scene has no layers or layers is not an array: " << scene["name"] << "\n";
			return false;
		}

		for (const auto& layer : scene["layers"])
		{
			const auto& validLayer = layer.contains("objects");
			if (!validLayer) continue;


			if (layer["name"].get<std::string>() != layerName)
				continue;
			
			for (const auto& obj : layer["objects"])
			{
				if (obj["id"] == id)
				{
					outObj = obj;
					return true;
				}
			}
		}
		return false;
	}

	void SceneManager::StartSceneManager()
	{
		LoadSceneBasicFeatures();
		LoadSceneGameObjects();

		AwakeSceneObjects();
		StartSceneObjects();
	}

	std::string SceneManager::GetLayerNameObjectByID(int& id)
	{
		auto& scene = GetScene(m_currentScene);

		if (!scene.contains("layers") || !scene["layers"].is_array()) {
			std::cout << "WARNING: Scene has no layers or layers is not an array: " << scene["name"] << "\n";
			return "";
		}

		for (const auto& layer : scene["layers"])
		{
			if (!layer.contains("objects")) continue;

			for (const auto& obj : layer["objects"])
			{
				if (obj.contains("id") && obj["id"] == id)
				{
					return layer["name"].get<std::string>();
				}
			}
		}

		return "";
	}

	bool SceneManager::IsCameraDirty()
	{
		return m_cameraDirty;
	}

	void SceneManager::ClearCameraDirty()
	{
		m_cameraDirty = false;
	}

	void ratchet::SceneManager::CheckAndBuildScenes()
	{
		// #TODO: FOLOSESTE RELATIVE PATH IN LOC DE FULL PATH
		m_baseScenePath = "F:/Users/mihai/Documents/GitHub/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/Levels/Scenes/";

		const std::string combinedPath = m_baseScenePath + "GameScenes.json";

		m_sceneFiles = {
			{SceneType::MainMenu, "Main Menu.tmj"},
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
		{
			float timeStep = 1.0f / 120.0f;
			if (m_currentScene != SceneType::MainMenu)
			{
				if (!Physics::IsSimulationEnabled())
				{
					Physics::SetSimulationEnabled(true);
				}
				Physics::update(timeStep);
			}
			else
			{
				if (Physics::IsSimulationEnabled())
				{
					Physics::SetSimulationEnabled(false);
				}
				Physics::SetSimulationEnabled(false);
			}

			for (auto i = 0u; i < GameObject::s_gameObjects.size(); i++)
			{
				GameObject::clearQueuedObjectsToDestroy();
				if (auto obj = GameObject::s_gameObjects[i])
				{
					if (obj)
					{
						obj->update();
					}
				}
				else
				{
					TRACE_CHANNEL("GAME_OBJECT", "Cannot update null game object of index [", i, "].");
				}
			}
		}
	}

	void SceneManager::renderSceneObjects(sf::RenderTarget& target)
	{
		{
			Player* player = nullptr;

			for (auto* obj : GameObject::s_gameObjects)
			{
				if ((player = dynamic_cast<Player*>(obj)))
					break;
			}

			if (player)
			{
				sf::View view = target.getView();
				view.setCenter(
					player->getCollider()->getBody()->GetPosition().x,
					player->getCollider()->getBody()->GetPosition().y
				);
				target.setView(view);
			}

			for (auto* obj : GameObject::s_gameObjects)
			{
				if (obj)
				{
					obj->render(target);
				}
			}
		}

	}

	void SceneManager::LoadScene(SceneType scene)
	{
		if (m_currentScene != scene)
		{
			m_currentScene = scene;
		}

		ClearSceneObjects();
		LoadSceneBasicFeatures();

		LoadSceneGameObjects();
		m_cameraDirty = true;
	}

	void SceneManager::LoadNextScene()
	{
		IncreaseSceneIndex();
		m_currentScene = static_cast<SceneType>(m_sceneIndex);

		Physics::SetSimulationEnabled(false);

		Weapon::ClearWeaponList();
		Weapon::ClearBulletList();

		StopUpdating();

		ClearSceneObjects();

		m_isrendering = false;
		m_isUpdating = false;

		LoadSceneBasicFeatures();

		LoadSceneGameObjects();

		AwakeSceneObjects();
		StartSceneObjects();



		m_isrendering = true;
		m_isUpdating = true;

		m_cameraDirty = true;

		Physics::SetSimulationEnabled(true);
	}

	void SceneManager::IncreaseSceneIndex()
	{
		m_sceneIndex++;

		if (m_sceneIndex >= m_sceneFiles.size())
		{
			m_sceneIndex = 0;
		}
	}

	void SceneManager::LoadSceneBasicFeatures()
	{
		std::string sceneName = m_sceneFiles[m_currentScene];

		if (!m_allScenes.contains("scenes")) {
			std::cout << "ERROR: GameScenes.json does not contain 'Scenes' key\n";
			return;
		}

		auto& scenesNode = m_allScenes["scenes"];
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
			const auto& layerName = layer["name"].get<std::string>();
			if (layerName == "Scene Features")
			{
				const auto& validLayer = layer.contains("objects");
				if (!validLayer) continue;

				for (const auto& obj : layer["objects"])
				{
					if (obj["name"] == "Scene Camera")
					{
						for (const auto& prop : obj["properties"])
						{
							const auto& propertyName = prop["name"].get<std::string>();
							const auto& propertyValue = prop["value"];
							if (propertyName == "cameraZoom")
							{
								sc_defaultZoom = propertyValue.get<float>();
							}
						}
					}
					if (obj["name"] == "Scene Object Dimension")
					{
						for (const auto& prop : obj["properties"])
						{
							const auto& propertyName = prop["name"].get<std::string>();
							const auto& propertyValue = prop["value"];
							if (propertyName == "tileToGameScale")
							{
								sc_tiledToGameScale = propertyValue.get<float>();
							}
						}
					}
				}
			}
		}
	}

	void SceneManager::StartSceneObjects()
	{
		for (auto* obj : GameObject::s_gameObjects)
		{
			obj->Start();
		}
	}

	void SceneManager::AwakeSceneObjects()
	{
		for (auto* obj : GameObject::s_gameObjects)
		{
			obj->Awake();
		}
	}

	void SceneManager::LoadSceneGameObjects()
	{
		std::string sceneName = m_sceneFiles[m_currentScene];

		if (!m_allScenes.contains("scenes")) {
			std::cout << "ERROR: GameScenes.json does not contain 'Scenes' key\n";
			return;
		}

		auto& scenesNode = m_allScenes["scenes"];
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
						if (!PrefabAssets::Get().isBulletConfigExists(config.m_objectID))
						{
							PrefabAssets::Get().RegisterBulletConfig(config.m_objectID, &config);
						}
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

						if (!PrefabAssets::Get().isWeaponConfigExists(config.m_objectID))
						{
							PrefabAssets::Get().RegisterWeaponConfig(config.m_objectID, &config);
						}
						succeeded = true;
					}
				}
				else if (layerName == "Click Buttons")
				{
					auto config = UIButtonConfig();
					if (config.deserialise(obj))
					{
						GameObject::s_gameObjects.push_back(new UIClickButton(config));
					}

					succeeded = true;
				}
				else if (layerName == "Slider Buttons")
				{
					if (obj["name"] == "Slider Button")
					{
						auto config = UISliderButtonConfig();

						if (config.deserialise(obj))
						{
							GameObject::s_gameObjects.push_back(new UISliderButton(config));
						}
					}
					else if (obj["name"] == "Back Button")
					{
						auto config = UIButtonConfig();

						if (config.deserialise(obj))
						{
							GameObject::s_gameObjects.push_back(new UIClickButton(config));
						}
					}
					succeeded = true;
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
		GameObject::clearQueuedObjectsToDestroy();

		for (auto* obj : GameObject::s_gameObjects)
		{
			if (obj != nullptr)
			{
				delete obj;
				obj = nullptr;
			}
		}

		GameObject::s_gameObjects.clear();
	}


	SceneManager& SceneManager::Get()
	{
		static SceneManager instance;
		return instance;
	}

	nlohmann::json& ratchet::SceneManager::GetScene(SceneType type)
	{
		std::string fileName = m_sceneFiles[type];

		return m_allScenes["scenes"][fileName];
	}

	void SceneManager::StopUpdating()
	{
		for (auto& obj : GameObject::s_gameObjects)
		{
			if (obj->m_activeGameObject)
			{
				obj->m_activeGameObject = false;
			}
		}
	}

	void SceneManager::StopRendering()
	{
		for (auto& obj : GameObject::s_gameObjects)
		{
			if (obj->m_activeRenderer)
			{
				obj->m_activeRenderer = false;
			}
		}
	}
}

