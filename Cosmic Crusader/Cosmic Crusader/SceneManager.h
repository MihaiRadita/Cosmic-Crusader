#pragma once

#include "GameObject.h"
#include "Creature.h"
#include "game/Player.h"
#include "game/Tile.h"
#include "WeaponPickup.h"

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
		Playing =0, 
		Pause
	};

	class SceneManager
	{
	public:


		SceneManager();
		~SceneManager();
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

		//Getters
		static SceneManager* GetSceneManager();
		nlohmann::json& GetScene(SceneType type);


	private:

		std::map<SceneType, std::string> m_sceneFiles;
		SceneType m_currentScene;

		nlohmann::json m_allScenes;

		std::string m_baseScenePath;

		static SceneManager* m_sceneManager;

		int m_sceneIndex;

		bool m_isUpdating = true;

		SceneGameState m_currentGameSceneState;

		std::map<SceneType,  std::vector<GameObject>> m_sceneGameObjects;

		std::map<SceneType, std::vector<GameObjectConfig>>m_sceneGameObjectsConfigs;
	};
}

