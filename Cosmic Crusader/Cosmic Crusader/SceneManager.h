#pragma once

namespace ratchet
{
	namespace fs = std::filesystem;

	enum SceneType
	{
		MainMenu = 0,
		Level1
	};

	class SceneManager
	{
	public:


		SceneManager();
		~SceneManager();
		void CheckAndBuildScenes();
		void LoadCombinedScenes();


		static SceneManager* GetSceneManager();


		nlohmann::json& GetScene(SceneType type);


	private:

		std::map<SceneType, std::string> m_sceneFiles;
		SceneType m_currentScene;

		nlohmann::json m_allScenes;

		std::string SCENE_FOLDER;

		std::string m_baseScenePath;

		static SceneManager* m_sceneManager;
	};
}

