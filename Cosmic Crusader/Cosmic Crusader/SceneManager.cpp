#include "stdafx.h"
#include "SceneManager.h"


namespace ratchet
{
	ratchet::SceneManager::SceneManager()
	{
		CheckAndBuildScenes();
		LoadCombinedScenes();
		m_currentScene = SceneType::MainMenu;
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
		SCENE_FOLDER = "F:/Users/mihai/Documents/GitHub/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/Levels/Scenes";

		fs::create_directories(SCENE_FOLDER);

		const std::string combinedPath = SCENE_FOLDER + "GameScenes.json";


		m_sceneFiles = {
			{SceneType::MainMenu, "MainMenu.tmj"},
			{SceneType::Level1, "Level1.tmj"}
		};

		m_baseScenePath = SCENE_FOLDER;

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
		std::string combinedPath = SCENE_FOLDER + "GameScenes.json";

		if (!fs::exists(combinedPath))
		{
			std::cout << "ERROR! File does not exists!" << std::endl;
			return;
		}

		std::ifstream in(combinedPath);

		in >> m_allScenes;

		std::cout << "The Scene File has been created with scuccess!" << std::endl;

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

