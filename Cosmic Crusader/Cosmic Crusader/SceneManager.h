#pragma once

#include "GameObject.h"
#include "Creature.h"
#include "game/Player.h"
#include "game/Tile.h"
#include "WeaponPickup.h"
#include "UIClickButton.h"
#include "UISliderButton.h"
#include "Checkpoint.h"
#include "ActionTrigger.h"
#include "Obstacle.h"
#include "Item.h"

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

	enum class Resolution
	{ 
		HD = 0, 
		FullHD,
		DoubleK,
		ForthK
	};

	struct ResolutionInfo
	{
		std::string name;
		int width;
		int height;
	};

	class SceneManager
	{
	public:


		SceneManager(const SceneManager&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;

		void CheckAndBuildScenes();
		void LoadCombinedScenes();

		void updateSceneObjects();
		void renderSceneObjects(sf::RenderTarget& target);

		//Setters

		void LoadScene(SceneType scene);
		void LoadNextScene();
		void IncreaseSceneIndex();

		void SaveGame();
		void SaveSettings();
		void SaveSoundSettings();
		void SaveResolutionSettings();

		

		void SetNewGame();

		void LoadSceneGameObjects();

		void ClearSceneObjects();

		void LoadSceneBasicFeatures();

		void StartSceneObjects();
		void AwakeSceneObjects();

		void StopSoundtrack();

		void SetPauseMenuActive(bool active);

		float& GetMusicVolume();
		float& GetSoundEffectsVolume();

		void ClearDestroyedCharactersLists();
		void ClearDestroyedItemsList();

		void SetWindowResolution(const sf::Vector2u& newResolution);

		sf::FloatRect GetAspectRatio(sf::Vector2u windowSize, sf::Vector2f viewSize);


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


		bool m_isFullScreen;
		bool m_isInitialFullScreen;

		sf::Vector2f m_worldCenter;
		sf::Vector2f m_uiCenter;

		sf::Vector2f m_uiViewSize;
		sf::Vector2f m_worldViewSize;

		bool m_isViewFollow;

		bool IsCameraDirty();

		void UpdateMusicSoundtrack();

		void ClearCameraDirty();
		nlohmann::json* FindObjectById(int id, const std::string& layerName);

		SceneType GetCurrentScene();

		void StartSceneManager();

		std::string GetLayerNameObjectByID(int& id);

		void SetGameScenePauseState();


		void SetResolutionList();

		sf::View GetWorldView();
		sf::View GetUIView();

		sf::Vector2f m_cameraDiemsnions;

		Resolution& GetCurrentResolution();

		sf::Music m_sceneSoundtrack;
		float m_musicVolume;
		float m_initialMusicVolume;
		std::string m_musicSoundtrackPath;


		float m_soundEffectsVolume = 0.0f;

		sf::SoundBuffer m_pauseMenuSoundOnBuffer;
		sf::SoundBuffer m_pauseMenuSoundOffBuffer;
		sf::Sound m_pauseMenuSoundOn;
		sf::Sound m_pauseMenuSoundOff;

		std::string m_pauseMenuSoundOnPath;
		std::string m_pauseMenuSoundOffPath;

		std::map<SceneType, std::string> GetSceneFiles();

		std::vector<int>m_characters_destroyed_index;

		std::vector<int>m_characters_destroyed_ID;
		
		std::map<int, int>m_characters_destroyedID_index;
		std::map<int, int>m_items_destroyedID_index;

		nlohmann::json GetAllScenesFile();

		void ApplySceneView();

		void RestartLevel();

		std::map<Resolution, ResolutionInfo> m_resolutions;

	private:

		SceneManager();

		Resolution m_currentResolution;
		Resolution m_initialResolution;
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

