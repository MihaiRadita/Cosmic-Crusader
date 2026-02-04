#pragma once

#include "GameObject.h"
#include "Creature.h"
#include "game/Player.h"
#include "game/Tile.h"
#include "WeaponPickup.h"
#include "UIClickButton.h"
#include "UISliderButton.h"

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

		void LoadSceneGameObjects();

		void ClearSceneObjects();

		void LoadSceneBasicFeatures();

		void StartSceneObjects();
		void AwakeSceneObjects();

		//Getters
		static SceneManager& Get();
		nlohmann::json& GetScene(SceneType type);

		inline static float sc_tiledToGameScale = 0.0f;
		inline static float sc_defaultZoom = 0.0f;

		void StopUpdating();
		void StopRendering();

		bool m_isUpdating = true;
		bool m_isrendering = true;

		bool m_isPaused = false;

		sf::Vector2f m_worldCenter;
		sf::Vector2f m_uiCenter;

		bool IsCameraDirty();

		void ClearCameraDirty();
		bool FindObjectById(int& id, nlohmann::json& outObj, const std::string& layerName);

		SceneType GetCurrentScene();

		void StartSceneManager();

		std::string GetLayerNameObjectByID(int& id);

		void SetGameScenePauseState();

		sf::View GetWorldViewView();

		void ApplySceneView();

	private:

		SceneManager();

		std::map<SceneType, std::string> m_sceneFiles;
		SceneType m_currentScene;

		nlohmann::json m_allScenes;

		std::string m_baseScenePath;

		sf::View m_worldView;
		sf::View m_uiView;

		int m_sceneIndex;

		bool m_cameraDirty;


		SceneGameState m_currentGameSceneState;
	};
}

