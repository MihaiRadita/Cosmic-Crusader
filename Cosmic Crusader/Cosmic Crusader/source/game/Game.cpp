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
		m_window.create(sf::VideoMode(1280, 720), "Cosmic Crusader", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

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

			if (sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::F1)
			{
				WindowManager::DestroyWindow();
				m_window.close();

				auto& isFullScreen = SceneManager::Get().m_isFullScreen;
				auto& isInitialFullScreen = SceneManager::Get().m_isInitialFullScreen;

				isFullScreen = !isFullScreen;



				if (isFullScreen)
				{
					sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

					m_window.create(fullscreenMode, "Cosmic Crusader", sf::Style::None);
					WindowManager::create(&m_window);

					SceneManager::Get().SaveSettings();

				}
				else
				{
					sf::Vector2u resolution(
						SceneManager::Get().m_resolutions[SceneManager::Get().GetCurrentResolution()].width,
						SceneManager::Get().m_resolutions[SceneManager::Get().GetCurrentResolution()].height
					);

					m_window.create(sf::VideoMode(resolution.x, resolution.y), "Cosmic Crusader", sf::Style::Titlebar | sf::Style::Close);
					WindowManager::create(&m_window);

					SceneManager::Get().SetWindowResolution(resolution);

					SceneManager::Get().SaveSettings();

				}

				isInitialFullScreen = isFullScreen;
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

			if (sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::R)
			{
				auto& sceneManager = SceneManager::Get();
				const auto& resolution = sceneManager.m_resolutions[SceneManager::Get().GetCurrentResolution()];
				SceneManager::Get().SetWindowResolution(sf::Vector2u(resolution.width, resolution.height));

				SceneManager::Get().SaveSettings();

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
				else if (auto checkPoint = dynamic_cast<Checkpoint*>(obj))
				{
					checkPoint->handleCheckPointEvent(sfEvent);
				}
				else if (auto item = dynamic_cast<Item*>(obj))
				{
					item->handleItemtEvent(sfEvent);
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
		static sf::Clock clock;
		s_deltaTime = clock.restart().asSeconds();

		handleEvents();

		SceneManager::Get().updateSceneObjects();
	}

	void Game::awake()
	{
		SceneManager::Get().AwakeSceneObjects();
	}

	void Game::start()
	{
		SceneManager::Get().StartSceneManager();
		
		//applySceneView();
		SceneManager::Get().StartSceneObjects();
		startWindow();
	}

	sf::VideoMode Game::GetFullScreenMode()
	{
		return fullscreenMode;
	}

	bool Game::GetIsFullScreen()
	{
		return m_isFullScreen;
	}

	void Game::startWindow()
	{

		auto& isFullScreen = SceneManager::Get().m_isFullScreen;



		if (isFullScreen)
		{
			sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

			m_window.create(fullscreenMode, "Cosmic Crusader", sf::Style::Fullscreen);
			WindowManager::create(&m_window);

		}
		else
		{
			sf::Vector2u resolution(
				SceneManager::Get().m_resolutions[SceneManager::Get().GetCurrentResolution()].width,
				SceneManager::Get().m_resolutions[SceneManager::Get().GetCurrentResolution()].height
			);

			m_window.create(sf::VideoMode(resolution.x, resolution.y), "Cosmic Crusader", sf::Style::Titlebar | sf::Style::Close);
			WindowManager::create(&m_window);

			SceneManager::Get().SetWindowResolution(resolution);
		}
	}

	void Game::render()
	{
		m_window.clear(sf::Color::Black);

		SceneManager::Get().renderSceneObjects(m_window);

		m_window.display();

	}

	float Game::getDeltaTime()
	{
		return s_deltaTime;
	}

	float Game::s_deltaTime = 0.016f;
}