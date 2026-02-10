#include "stdafx.h"
#include "Game.h"
#include "TileConfig.h"

#include "EnumMask.h"

namespace ratchet
{
	void Game::spawnObjects()
	{
		SceneManager::Get();
		SceneManager::Get().StartSceneManager();
	}

	void Game::applySceneView()
	{
		SceneManager::Get().ApplySceneView();
	}

	Game::Game()
	{
		initWindow();
		initPhysics();
		initWeaponManager();
	}

	Game::~Game()
	{
		Physics::SetSimulationEnabled(false);
		WindowManager::clear();


		for (auto& obj : GameObject::s_gameObjects)
		{
			delete obj;
		}
		GameObject::s_gameObjects.clear();
		PrefabAssets::Get().DestroyPrefabAssets();
		Physics::DestroyPhysicsInstance();

	}

	void Game::initWindow()
	{
		m_window.create(sf::VideoMode(1280, 720), "Cosmic Crusader", sf::Style::Titlebar | sf::Style::Close);

		WindowManager::create(&m_window);
		// m_window.setFramerateLimit(60);
	}

	void Game::initPhysics()
	{

	}

	void Game::initWeaponManager()
	{
		WeaponManager::instance()->addAllWeapons();
	}

	const sf::RenderWindow& Game::getWindow() const
	{
		return m_window;
	}

	void Game::handleEvents()
	{
		sf::Event sfEvent;
		while (m_window.pollEvent(sfEvent))
		{
			if (sfEvent.type == sf::Event::Closed)
			{
				m_window.close();
			}

			if (sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::Escape)
			{
				if (SceneManager::Get().GetCurrentScene() != SceneType::MainMenu)
				{
					SceneManager::Get().SetGameScenePauseState();

					if (SceneManager::Get().m_isPaused)
					{
						WindowManager::Get()->setKeyRepeatEnabled(false);
					}
					else
					{
						WindowManager::Get()->setKeyRepeatEnabled(true);
					}
				}
			}


			if (sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::G)
			{
				m_window.clear(sf::Color::Black);
				m_window.display();

				SceneManager::Get().LoadNextScene();
			}

			for (const auto& obj : GameObject::s_gameObjects)
			{
				if (auto uiButton = dynamic_cast<UIClickButton*>(obj))
				{
					uiButton->handleUIEvent(sfEvent);

				}
				else if (auto uiSlider = dynamic_cast<UISliderButton*>(obj))
				{
					uiSlider->handleButtonsEvent(sfEvent);
				}
				if (auto player = dynamic_cast<Player*>(obj))
				{
					player->handleEvent(sfEvent);
				}
				else if (auto selfCreature = dynamic_cast<SelfControlledCreature*>(obj))
				{
					selfCreature->handleSelfCreatureEvent();
				}
			}
		}

		for (const auto& obj : GameObject::s_gameObjects)
		{
			if (auto bullet = dynamic_cast<Bullet*>(obj))
			{
				bullet->bulletHandleEvents();
			}
		}
	}
	void Game::update()
	{
		handleEvents();

		if (SceneManager::Get().IsCameraDirty())
		{
			applySceneView();
			SceneManager::Get().ClearCameraDirty();

		}
		
		SceneManager::Get().updateSceneObjects();
	}

	void Game::awake()
	{
		SceneManager::Get().AwakeSceneObjects();
	}

	void Game::start()
	{
		spawnObjects();
		applySceneView();
		SceneManager::Get().StartSceneObjects();
	}

	void Game::render()
	{
		m_window.clear(sf::Color::Black);

		SceneManager::Get().renderSceneObjects(m_window);

		m_window.display();

	}

}