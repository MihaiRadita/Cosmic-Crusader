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
		initAudioManager();
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
		m_window.setFramerateLimit(120);

		WindowManager::create(&m_window);
	}

	void Game::initPhysics()
	{
		
	}

	void Game::initWeaponManager()
	{
		WeaponManager::instance()->addAllWeapons();
	}

	void Game::initAudioManager()
	{
		AudioManager::Initialize();
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


		static float timePassed = 0.0f;
		if (SceneManager::Get().GetCurrentScene() != SceneType::MainMenu)
		{
			timePassed += s_deltaTime;

			if (timePassed > 2.0f)
			{
				updatePhysicsSystem();
			}
		}
		else
		{
			timePassed = 0.0f;
		}

		SceneManager::Get().updateSceneObjects();
	}

	void Game::updatePhysicsSystem()
	{
		const auto& worldView = SceneManager::Get().GetWorldView();

		sf::FloatRect view = worldView.getViewport(); // NU asta
		sf::Vector2f center = worldView.getCenter();
		sf::Vector2f size = worldView.getSize();

		float halfW = size.x * 0.8;
		float halfH = size.y * 0.8;


		for (auto* obj : GameObject::s_gameObjects)
		{
			if (!obj || !obj->m_collider)
				continue;

			if (obj->m_objectType == ObjectType::UI ||
				obj->m_objectType == ObjectType::HUD)
				continue;

			if (dynamic_cast<Player*>(obj))
				continue;
			if (dynamic_cast<Bullet*>(obj))
				continue;


			b2Body* body = obj->m_collider->getBody();
			if (!body)
				continue;


			const auto* collider = obj->m_collider;
			const auto topLeftPoint = collider->GetTopLeftPoint();
			const auto bottomRightPoint = collider->GetBottomRightPoint();
			const auto closestPointWithinColliderRectangleX = std::max(topLeftPoint.x, std::min(center.x, bottomRightPoint.x));
			const auto closestPointWithinColliderRectangleY = std::max(topLeftPoint.y, std::min(center.y, bottomRightPoint.y));

			const auto pos = sf::Vector2f(closestPointWithinColliderRectangleX, closestPointWithinColliderRectangleY);
		

			float dx = pos.x - center.x;
			float dy = pos.y - center.y;

			bool inside =
				std::abs(dx) <= halfW &&
				std::abs(dy) <= halfH;

			if (obj->m_objectId == 5625)
			{
				if (!inside)
				{
					bool i = inside;
				}
			}

			if (obj->m_objectId == 5536)
			{
				if (!inside)
				{
					bool i = inside;
				}
			}


			if (obj->m_objectId == 5397)
			{
				if (!inside)
				{
					bool i = inside;
				}
			}

			if (obj->m_objectId == 6023)
			{
				if (!inside)
				{
					bool i = inside;
				}
			}

			if (obj->m_objectId == 5204)
			{
				if (!inside)
				{
					bool i = inside;
				}
				else
				{
					bool t = inside;
				}
			}

			if (obj->m_objectId == 5112)
			{
				if (!inside)
				{
					bool i = inside;
				}
				else
				{
					bool t = inside;
				}
			}
			

			if (body->IsEnabled() != inside)
			{
				body->SetEnabled(inside);
			}

			if(obj->m_activeGameObject != inside)
			{
				obj->m_activeGameObject = inside;
			}

			if (obj->m_activeRenderer != inside)
			{
				obj->m_activeRenderer = inside;
			}
		}
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