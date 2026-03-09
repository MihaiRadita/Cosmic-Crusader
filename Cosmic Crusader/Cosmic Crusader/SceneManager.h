#pragma once

#include "GameObject.h"
#include "Creature.h"
#include "game/Player.h"
#include "game/Tile.h"
#include "WeaponPickup.h"
#include "UIClickButton.h"
#include "UISliderButton.h"
#include "Checkpoint.h"

#include "physics/Physics.h"

#include "WindowManager.h"

#include "PrefabAssets.h"

#include "SelfControlledCreature.h""

namespace ratchet
{
	namespace fs = std::filesystem;

	enum SceneType
	{
		MainMenu = 0,
		Level1
	};

	enum SceneGameState
	{
		Playing = 0, 
		Pause
	};

	class SceneManager
	{
	public:


		SceneManager(const SceneManager&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;
		//~SceneManager();
		void CheckAndBuildScenes();
		void LoadCombinedScenes();

		void updateSceneObjects();
		void renderSceneObjects(sf::RenderTarget& target);

		//Setters

		void LoadScene(SceneType scene);
		void LoadNextScene();
		void IncreaseSceneIndex();

		void SaveGame();

		void SetNewGame();

		void LoadSceneGameObjects();

		void ClearSceneObjects();

		void LoadSceneBasicFeatures();

		void StartSceneObjects();
		void AwakeSceneObjects();

		void SetPauseMenuActive(bool active);


		//Getters
		static SceneManager& Get();
		nlohmann::json& GetScene(SceneType type);

		inline static float sc_tiledToGameScale = 0.0f;
		inline static float sc_defaultZoom = 0.0f;

		void StopUpdating();
		void StopRendering();

		bool m_isUpdating = true;
		bool m_isrendering = true;
		bool m_isPuaseEventActvie = false;

		bool m_gameOver = false;

		bool m_isPaused = false;

		sf::Vector2f m_worldCenter;
		sf::Vector2f m_uiCenter;

		sf::Vector2f m_uiViewSize;

		bool IsCameraDirty();

		void ClearCameraDirty();
		nlohmann::json* FindObjectById(int id, const std::string& layerName);

		SceneType GetCurrentScene();

		void StartSceneManager();

		std::string GetLayerNameObjectByID(int& id);

		void SetGameScenePauseState();

		sf::View GetWorldView();
		sf::View GetUIView();

		std::map<SceneType, std::string> GetSceneFiles();

		std::vector<int>m_characters_destroyed_index;
		std::vector<int>m_characters_destroyed_ID;

		nlohmann::json GetAllScenesFile();

		void ApplySceneView();

		void RestartLevel();

	private:

		SceneManager();

		std::map<SceneType, std::string> m_sceneFiles;
		SceneType m_currentScene;

		nlohmann::json m_allScenes;

		sf::RectangleShape m_uiTestShape;

		std::string m_baseScenePath;

		sf::View m_worldView;
		sf::View m_uiView;

		int m_sceneIndex;

		bool m_cameraDirty;


		SceneGameState m_currentGameSceneState;
	};
}

