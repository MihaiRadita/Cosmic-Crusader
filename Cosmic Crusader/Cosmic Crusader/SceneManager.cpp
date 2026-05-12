#include "stdafx.h"
#include "SceneManager.h"
#include "Weapon.h"

#include "game/Game.h"

namespace ratchet
{
	ratchet::SceneManager::SceneManager()
	{
		CheckAndBuildScenes();

		m_currentScene = SceneType::MainMenu;
		m_currentGameSceneState = SceneGameState::Playing;
		m_sceneIndex = static_cast<int>(m_currentScene);
	}

	nlohmann::json* SceneManager::FindObjectById(int id, const std::string& layerName)
	{
		auto& scene = GetScene(m_currentScene);

		for (auto& layer : scene["layers"])
		{
			if (!layer.contains("objects")) continue;

			if (layer["name"] != layerName) continue;

			for (auto& obj : layer["objects"])
			{
				if (obj["id"] == id)
				{
					return &obj; 
				}
			}
		}

		return nullptr;
	}

	SceneType SceneManager::GetCurrentScene()
	{
		return m_currentScene;
	}

	void SceneManager::StartSceneManager()
	{
		LoadCombinedScenes();
		LoadSceneBasicFeatures();
		SetResolutionList();
		LoadSceneGameObjects();

		AwakeSceneObjects();
		StartSceneObjects();
	}

	void SceneManager::StartSceneObjects()
	{

		if (!m_pauseMenuSoundOffBuffer.loadFromFile(m_pauseMenuSoundOffPath))
		{
			std::cout << "Sund not loaded!" << std::endl;
		}

		if (!m_pauseMenuSoundOnBuffer.loadFromFile(m_pauseMenuSoundOnPath))
		{
			std::cout << "Sund not loaded!" << std::endl;
		}

		m_pauseMenuSoundOn = sf::Sound();

		m_pauseMenuSoundOn.setBuffer(m_pauseMenuSoundOnBuffer);
		m_pauseMenuSoundOff.setBuffer(m_pauseMenuSoundOffBuffer);

		m_pauseMenuSoundOn.setVolume(5.F);
		m_pauseMenuSoundOff.setVolume(5.f);

		m_pauseMenuSoundOn.setLoop(false);
		m_pauseMenuSoundOff.setLoop(false);

		m_isViewFollow = true;

		m_worldView.setSize(
			m_cameraDiemsnions.x * sc_defaultZoom,
			m_cameraDiemsnions.y * sc_defaultZoom
		);

		m_worldView.setCenter(m_worldCenter);

		m_uiViewSize = m_cameraDiemsnions;

		m_uiView.setSize(m_uiViewSize);
		m_uiView.setCenter(
			m_uiViewSize.x / 2.f,
			m_uiViewSize.y / 2.f
		);

		SetWindowResolution(
			sf::Vector2u(
				m_resolutions[m_currentResolution].width,
				m_resolutions[m_currentResolution].height
			)
		);

		for (auto* obj : GameObject::s_gameObjects)
		{

			obj->Start();
		}

		if (m_currentScene == SceneType::Level1)
		{
			m_uiTestShape.setSize(sf::Vector2f(20.f, 20.f));
			m_uiTestShape.setScale(sf::Vector2f(1.0f, 1.0f));
			m_uiTestShape.setFillColor(sf::Color::Green);
			m_uiTestShape.setPosition(sf::Vector2f(m_uiView.getCenter().x, m_uiView.getCenter().y));
		}
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

	void SceneManager::SetGameScenePauseState()
	{
		m_isPaused = !m_isPaused;

		SetPauseMenuActive(m_isPaused);

		if (m_isPaused)
		{
			m_pauseMenuSoundOn.play();
		}
		else
		{
			m_pauseMenuSoundOff.play();
		}
	}

	void SceneManager::SetPauseMenuActive(bool active)
	{
		for (auto* obj : GameObject::s_gameObjects)
		{
		
			if (obj->m_objectType == ObjectType::UI)
			{
				if (active)
				{
					if (auto* button = dynamic_cast<UIButton*>(obj))
					{
						if (button->m_parentNameState == ButtonNameState::None)
						{
							button->SetActiveObject(active);
							button->SetActiveRenderer(active);
						}
				
					}

					if (auto* text = dynamic_cast<UIText*>(obj))
					{
						if (text->m_textConnectedObject == TextConnectedObject::None)
						{
							text->SetActiveObject(active);
							text->SetActiveRenderer(active);
						}
					}
				}
				else
				{
					obj->SetActiveObject(active);
					obj->SetActiveRenderer(active);
				}
			}
		}
	}

	float& SceneManager::GetMusicVolume()
	{
		return m_musicVolume;
	}

	float& SceneManager::GetSoundEffectsVolume()
	{
		return m_soundEffectsVolume;
	}

	void SceneManager::ClearDestroyedCharactersLists()
	{
		m_characters_destroyedID_index.clear();
	}

	void SceneManager::SetWindowResolution(const sf::Vector2u& newResolution)
	{

		if (m_isFullScreen)
		{
			return;
		}
	
		WindowManager::Get()->setSize(newResolution);

		sf::Vector2u windowSize = newResolution;

		sf::FloatRect worldViewport = GetAspectRatio(windowSize, m_worldView.getSize());
		sf::FloatRect uiViewport = GetAspectRatio(windowSize, m_uiView.getSize());

		m_worldView.setViewport(worldViewport);
		m_uiView.setViewport(uiViewport);

		m_initialResolution = m_currentResolution;

	}

	sf::FloatRect SceneManager::GetAspectRatio(sf::Vector2u windowSize, sf::Vector2f viewSize)
	{
		float windowRatio = (float)windowSize.x / (float)windowSize.y;
		float viewRatio = viewSize.x / viewSize.y;

		float sizeX = 1.f;
		float sizeY = 1.f;
		float posX = 0.f;
		float posY = 0.f;

		if (windowRatio > viewRatio)
		{
			sizeX = viewRatio / windowRatio;
			posX = (1.f - sizeX) / 2.f;
		}
		else
		{
			sizeY = windowRatio / viewRatio;
			posY = (1.f - sizeY) / 2.f;
		}

		return sf::FloatRect(posX, posY, sizeX, sizeY);
	}

	void SceneManager::SetResolutionList()
	{
		m_resolutions[Resolution::HD] = { "1280X720", 1280, 720 };
		m_resolutions[Resolution::FullHD] = { "1920X1080", 1920, 1080 };
		m_resolutions[Resolution::DoubleK] = { "2560X1440", 2560, 1440 };
		m_resolutions[Resolution::ForthK] = { "3840X2160", 3840, 2160 };
	}

	sf::View SceneManager::GetWorldView()
	{
		return m_worldView;
	}

	sf::View SceneManager::GetUIView()
	{
		return m_uiView;
	}

	Resolution& SceneManager::GetCurrentResolution()
	{
		return m_currentResolution;
	}

	std::map<SceneType, std::string> SceneManager::GetSceneFiles()
	{
		return m_sceneFiles;
	}

	nlohmann::json SceneManager::GetAllScenesFile()
	{
		return m_allScenes;
	}

	void SceneManager::ApplySceneView()
	{
		std::cout << "THE ZOOM : " << sc_defaultZoom << std::endl;
		sf::View view = SceneManager::Get().GetWorldView();

		float defaultWidth = view.getSize().x;
		float defaultHeight = view.getSize().y;

		view.zoom(sc_defaultZoom);
		WindowManager::Get()->setView(view);

		float zoomX = defaultWidth / view.getSize().x;
		float zoomY = defaultHeight / view.getSize().y;

		std::cout << "Zoom applied: X=" << zoomX << " Y=" << zoomY << std::endl;

		std::cout << "YAAYYYY!" << std::endl;
	}

	void SceneManager::RestartLevel()
	{
		for (auto* object : GameObject::s_gameObjects)
		{
			if (object->m_objectType != ObjectType::UI)
			{
				object->m_activeRenderer = false;
			}
		}

		WindowManager::Get()->clear(sf::Color::Black);
		WindowManager::Get()->display();

		Timer timer;

		if (m_gameOver)
		{
			while (m_gameOver)
			{
				if (timer.GetElapsed().asSeconds() >= 2.0f)
				{
					m_gameOver = false;
				}
			}
			if (!m_gameOver)
			{
				for (auto* object : GameObject::s_gameObjects)
				{
					if (object->m_objectType != ObjectType::UI)
					{
						object->m_activeRenderer = true;
					}

					auto* player = dynamic_cast<Player*>(object);
					auto* enemy = dynamic_cast<SelfControlledCreature*>(object);

					if (player)
					{
						player->RestartObjectFeatures();
					}

					if (enemy && !enemy->m_isDeath)
					{
						enemy->RestartObjectFeatures();
					}
				}

				if(!m_characters_destroyedID_index.empty())
				{
					const auto& sceneFiles = SceneManager::Get().GetSceneFiles();
					std::string sceneName = SceneManager::Get().GetSceneFiles()[SceneManager::Get().GetCurrentScene()];
					const auto& allScenes = SceneManager::Get().GetAllScenesFile();

					if (sceneName == "Main Menu")
					{
						return;
					}

					if (!allScenes.contains("scenes")) {
						std::cout << "ERROR: GameScenes.json does not contain 'Scenes' key\n";
						return;
					}

					auto& scenesNode = allScenes["scenes"];
					if (!scenesNode.contains(sceneName)) {
						std::cout << "ERROR: Scene not found in GameScenes.json: " << sceneName << "\n";
						return;
					}

					auto& sceneJson = scenesNode[sceneName];

					if (!sceneJson.contains("layers") || !sceneJson["layers"].is_array()) {
						std::cout << "WARNING: Scene has no layers or layers is not an array: " << sceneName << "\n";
						return;
					}

					for (auto& layer : sceneJson["layers"])
					{
						const auto& validLayer = layer.contains("objects");
						if (!validLayer) continue;

						const auto& layerName = layer["name"].get<std::string>();

						if (layerName == "Enemies")
						{
							for (auto& obj : layer["objects"])
							{
								std::string objName = obj["name"];

								if (objName == "Enemy" || objName =="Enemy2")
								{
									const auto& enemyID = obj["id"];

									for (auto& detryedCharacters : m_characters_destroyedID_index)
									{
										if (enemyID == detryedCharacters.first)
										{
											auto& characterIndex = detryedCharacters.second;

											auto config = SelfControlledCreatureConfig();
											auto* configPtr = &config;

											if (config.deserialise(obj))
											{
												GameObject::s_gameObjects.insert(GameObject::s_gameObjects.begin() + characterIndex,
													new SelfControlledCreature(config));

												if (auto* enemy1 = dynamic_cast<SelfControlledCreature*>(GameObject::s_gameObjects[characterIndex]))
												{
													if (enemy1->m_objectId == enemyID)
													{
														enemy1->Start();
#ifdef IS_RATCHET_DEBUG
														enemy1->setDebugDraw(true);
#endif
													}

												}
											}
											break;
										}
									}
								}
							}
							SceneManager::Get().ClearDestroyedCharactersLists();
						}
					}
				}
			}
		}
	}

	bool SceneManager::IsCameraDirty()
	{
		return m_cameraDirty;
	}

	void SceneManager::ClearCameraDirty()
	{
		m_cameraDirty = false;
	}

	void SceneManager::UpdateMusicSoundtrack()
	{
		if (m_currentScene == SceneType::MainMenu)
		{
			if (m_sceneSoundtrack.getStatus() != sf::Music::Playing)
			{
				m_sceneSoundtrack.setVolume(m_musicVolume);
				m_sceneSoundtrack.setLoop(true);
				m_sceneSoundtrack.play();
			}
			else
			{
				if (m_initialMusicVolume != m_musicVolume)
				{
					m_sceneSoundtrack.setVolume(m_musicVolume);
					m_initialMusicVolume = m_musicVolume;
				}
			}

		}
		else 
		{
			if (!m_isPaused)
			{
				if (m_sceneSoundtrack.getStatus() != sf::Music::Playing)
				{
					m_sceneSoundtrack.setVolume(m_musicVolume);
					m_sceneSoundtrack.setLoop(true);
					m_sceneSoundtrack.play();
				}
			}
			else
			{
				if (m_sceneSoundtrack.getStatus() == sf::Music::Playing)
				{
					m_sceneSoundtrack.pause();

					if (m_initialMusicVolume != m_musicVolume)
					{
						m_sceneSoundtrack.setVolume(m_musicVolume);
						m_initialMusicVolume = m_musicVolume;
					}
				}
			}
		}
		
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
		UpdateMusicSoundtrack();

		if(!m_isPaused)
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
		else
		{
			for (auto i = 0u; i < GameObject::s_gameObjects.size(); i++)
			{
				GameObject::clearQueuedObjectsToDestroy();

				if (auto obj = GameObject::s_gameObjects[i])
				{
					if (obj)
					{
						if (obj->m_objectType == ObjectType::UI)
						{
							obj->update();
						}
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
		Player* player = nullptr;

		for (auto* obj : GameObject::s_gameObjects)
		{
			if ((player = dynamic_cast<Player*>(obj)))
				break;
		}

		// Update camera
		if (player && m_isViewFollow)
		{
			m_worldView.setCenter(
				player->getCollider()->getBody()->GetPosition().x,
				player->getCollider()->getBody()->GetPosition().y
			);
		}

		// WORLD RENDER
		target.setView(m_worldView);

		for (auto* obj : GameObject::s_gameObjects)
		{
			if (obj && obj->m_objectType == ObjectType::World)
			{
				obj->render(target);
			}
		}

		// UI RENDER
		target.setView(m_uiView);

		if (m_currentScene == SceneType::Level1)
		{
			target.draw(m_uiTestShape);
		}

		for (auto* obj : GameObject::s_gameObjects)
		{
			if (obj && obj->m_objectType == ObjectType::UI)
			{
				obj->render(target);
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

		m_isPaused = false;

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

	void SceneManager::SaveGame()
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
		
		for (auto& layer : sceneJson["layers"])
		{
			const auto& validLayer = layer.contains("objects");
			if (!validLayer) continue;

			const auto& layerName = layer["name"].get<std::string>();

			if (layerName == "Player")
			{
				for (auto& obj : layer["objects"])
				{
					if (obj["name"] == "Player")
					{
						auto& playerData = obj;
						for (auto& object : GameObject::s_gameObjects)
						{
							auto* player = dynamic_cast<Player*>(object);

							if (player)
							{
								player->serialise(playerData);
							}
						}
					}
				}
			}
		}

		std::string combinedPath = m_baseScenePath + "GameScenes.json";

		if (!fs::exists(combinedPath))
		{
			std::cout << "ERROR! File does not exists!" << std::endl;
			return;
		}

		std::ofstream out(combinedPath);

		out << m_allScenes;

		std::cout << "The Scene File has been created with scuccess!" << std::endl;


	}

	void SceneManager::SaveSettings()
	{

		if (!m_allScenes.contains("scenes")) {
			std::cout << "ERROR: GameScenes.json does not contain 'scenes' key\n";
			return;
		}

		auto& scenesNode = m_allScenes["scenes"];

		for (auto& [sceneName, sceneJson] : scenesNode.items())
		{
			if (!sceneJson.contains("layers") || !sceneJson["layers"].is_array()) {
				std::cout << "WARNING: Scene has no layers or layers is not an array: " << sceneName << "\n";
				continue;
			}

			for (auto& layer : sceneJson["layers"])
			{
				std::string layerName = layer["name"];

				for (auto& obj : layer["objects"])
				{
					std::string objName = obj["name"];

					if (layerName == "Scene Features")
					{
						if (objName == "Scene Resolution")
						{
							for (auto& prop : obj["properties"])
							{
								std::string propName = prop["name"];

								if (propName == "resolution")
								{
									prop["value"] = static_cast<int>(m_currentResolution);
								}

								if (propName == "isFullScreen")
								{
									if (m_isFullScreen != m_isInitialFullScreen)
									{
										prop["value"] = static_cast<bool>(m_isFullScreen);
									}
								}
							}
						}
						if (objName == "Music Soundtrack")
						{
							for (auto& prop : obj["properties"])
							{
								std::string propName = prop["name"];

								if (propName == "musicVolume")
								{
									prop["value"] = static_cast<float>(m_musicVolume);
								}
							}
						}

						if (objName == "Sound Effects")
						{
							for (auto& prop : obj["properties"])
							{
								std::string propName = prop["name"];

								if (propName == "soundEffectsVolume")
								{
									prop["value"] = static_cast<float>(m_soundEffectsVolume);
								}
							}
						}
					}
					else if (layerName ==  "Pause Menu Slider Buttons" || layerName == "Slider Buttons")
					{
						if (objName == "Slider Text Value")
						{
							nlohmann::json* textConnectedActionObjectProperty = nullptr;
							nlohmann::json* textValueProperty =nullptr;

							bool foundAll = false;

							for (auto& prop : obj["properties"])
							{
								if (prop["name"] == "textConnectedActionObject")
								{
									textConnectedActionObjectProperty = &prop;
								}
								else if (prop["name"] == "textValue")
								{
									textValueProperty = &prop;
								}

								foundAll = (textConnectedActionObjectProperty != nullptr) && (textValueProperty != nullptr);

								if (foundAll)
								{
									TextConnectedActionObject actionConnected =
										static_cast<TextConnectedActionObject>((*textConnectedActionObjectProperty)["value"].get<int>());

									for (auto& object : GameObject::s_gameObjects)
									{
										if (auto* uiSlider = dynamic_cast<UISliderButton*>(object))
										{
											if (uiSlider->m_UITextValue.m_textConnectedActionObject == actionConnected)
											{
												(*textValueProperty)["value"] = uiSlider->m_UITextValue.m_TextValue;
											}
										}
									}

									break; 
								}
							}
						}
					}
					
				}
			}
		}

		std::string combinedPath = m_baseScenePath + "GameScenes.json";

		if (!fs::exists(combinedPath))
		{
			std::cout << "ERROR! File does not exists!" << std::endl;
			return;
		}

		std::ofstream out(combinedPath);

		out << m_allScenes;

		std::cout << "The Scene File has been created with scuccess!" << std::endl;

	}

	void SceneManager::SetNewGame()
	{
		for (auto& [type, fileName] : m_sceneFiles)
		{
			if (type != SceneType::MainMenu)
			{
				std::string originalLevelPath = m_baseScenePath + fileName;

				if (!fs::exists(originalLevelPath))
				{
					std::cout << "ERROR! File does not exists!" << std::endl;
					return;
				}

				nlohmann::json originalSceneJson;

				std::ifstream in(originalLevelPath);
				 
				in >> originalSceneJson;

				std::string sceneName = fileName;

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

				if (!sceneJson.contains("layers")) {
					std::cout << "WARNING: Scene has no layers or layers is not an array: " << sceneName << "\n";
					return;
				}

				if (!originalSceneJson.contains("layers"))
				{
					std::cout << "WARNING: Scene has no layers or layers is not an array: " << fileName << "\n";
					return;
				}

				
				for (auto& layer : sceneJson["layers"])
				{
					const auto& validLayer = layer.contains("objects");
					if (!validLayer) continue;

					const auto& layerName = layer["name"].get<std::string>();

					if (layerName == "Player" || layerName == "Weapons")
					{
						for (auto& obj : layer["objects"])
						{
							if (obj["name"] == "Player" || obj["name"] == "Blaster")
							{
								if (!originalSceneJson.contains("layers"))
								{
									std::cout << "WARNING: Scene has no layers << " << std::endl;
									return;
								}

								for (auto& layer1 : originalSceneJson["layers"])
								{
									auto& layerName1 = layer1["name"];

									if (layerName1 == layerName)
									{
										for (auto& obj1 : layer1["objects"])
										{
											if (obj1["name"] == obj["name"] && obj1["id"] == obj["id"])
											{
												obj = obj1;
												break;
											}
										}

									}

								}
							}
						}
					}
				}

			}
		}

		std::string combinedPath = m_baseScenePath + "GameScenes.json";

		if (!fs::exists(combinedPath))
		{
			std::cout << "ERROR! File does not exists!" << std::endl;
			return;
		}

		std::ofstream out(combinedPath);

		out << m_allScenes;

		std::cout << "The Scene File has been created with scuccess!" << std::endl;
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

							if (propertyName == "worldCenterX")
							{
								m_worldCenter.x = propertyValue.get<float>();
							}

							if (propertyValue == "worldCenterY")
							{
								m_worldCenter.y = propertyValue.get<float>();
							}

							if (propertyName == "uiCenterX")
							{
								m_uiCenter.x = propertyValue.get<float>();
							}

							if (propertyName == "uiCenterY")
							{
								m_uiCenter.y = propertyValue.get<float>();
							}

							if (propertyName == "cameraDimensionX")
							{
								m_cameraDiemsnions.x = propertyValue.get<int>();
							}
							if (propertyName == "cameraDimensionY")
							{
								m_cameraDiemsnions.y = propertyValue.get<int>();
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

					if (obj["name"] == "Pause Menu Sounds")
					{
						for (const auto& prop : obj["properties"])
						{
							const auto& propertyName = prop["name"].get<std::string>();
							const auto& propertyValue = prop["value"];

							if (propertyName == "pauseMenuOff")
							{
								m_pauseMenuSoundOffPath = propertyValue.get<std::string>();
							}

							if (propertyName == "pauseMenuOn")
							{
								m_pauseMenuSoundOnPath = propertyValue.get<std::string>();
							}
						}
					}

					if (obj["name"] == "Scene Resolution")
					{
						for (const auto& prop : obj["properties"])
						{
							const auto& propertyName = prop["name"].get<std::string>();
							const auto& propertyValue = prop["value"];

							if (propertyName == "resolution")
							{
								m_currentResolution = static_cast<Resolution>(propertyValue.get<int>());
								m_initialResolution = m_currentResolution;
							}

							if (propertyName == "isFullScreen")
							{
								m_isFullScreen = propertyValue.get<bool>();
								
								m_isInitialFullScreen = m_isFullScreen;
							}
						}
					}
					if (obj["name"] == "Music Soundtrack")
					{
						for (const auto& prop : obj["properties"])
						{
							const auto& propertyName = prop["name"].get<std::string>();
							const auto& propertyValue = prop["value"];

							if (propertyName == "musicSoundtrackPath")
							{
								m_musicSoundtrackPath = propertyValue.get<std::string>();
							}

							if (propertyName == "musicVolume")
							{
								m_musicVolume = propertyValue.get<float>();
								m_initialMusicVolume = m_musicVolume;
							}
						}
					}

					if (obj["name"] == "Sound Effects")
					{
						for (const auto& prop : obj["properties"])
						{
							const auto& propertyName = prop["name"].get<std::string>();
							const auto& propertyValue = prop["value"];

							if (propertyName == "soundEffectsVolume")
							{
								m_soundEffectsVolume = propertyValue.get<float>();
							}
						}
					}
				}
			}
		}

		if (!m_sceneSoundtrack.openFromFile(m_musicSoundtrackPath))
		{
			std::cout << "music could Not opened!" << std::endl;
		}

		m_currentGameSceneState = SceneGameState::Playing;
		m_isPaused = false;
	}


	void SceneManager::AwakeSceneObjects()
	{
		for (auto* obj : GameObject::s_gameObjects)
		{
			obj->Awake();
		}
	}

	void SceneManager::StopSoundtrack()
	{
		m_sceneSoundtrack.stop();
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
							if (config.m_isWeaponAccessible)
							{
								GameObject::s_gameObjects.push_back(new WeaponPickup(config));
							}
						}

						if (!PrefabAssets::Get().isWeaponConfigExists(config.m_objectID))
						{
							PrefabAssets::Get().RegisterWeaponConfig(config.m_objectID, &config);
						}
						succeeded = true;
					}
				}
				else if (layerName == "Click Buttons" || layerName == "Pause Menu Click Buttons")
				{
					auto config = UIButtonConfig();
					if (config.deserialise(obj))
					{
						GameObject::s_gameObjects.push_back(new UIClickButton(config));
					}

					succeeded = true;
				}
				else if (layerName == "Slider Buttons" || layerName == "Pause Menu Slider Buttons")
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
					else if (obj["name"] == "UI Text")
					{
						auto config = UITextConfig();

						if (config.deserialise(obj))
						{
							GameObject::s_gameObjects.push_back(new UIText(config));
						}
					}
				}
				else if (layerName == "Check Points")
				{
					auto config = CheckpointConfig();

					if (config.deserialise(obj))
					{
						GameObject::s_gameObjects.push_back(new Checkpoint(config));
					}
				}
				else if (layerName == "Action Triggers")
				{
					auto config = ActionTriggerConfig();

					if (config.deserialise(obj))
					{
						GameObject::s_gameObjects.push_back(new ActionTrigger(config));
					}
				}
				succeeded = true;

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

