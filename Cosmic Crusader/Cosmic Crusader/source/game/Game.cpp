#include "stdafx.h"
#include "Game.h"
#include "TileConfig.h"

#include "EnumMask.h"

namespace ratchet
{
	//const float Game::sc_tiledToGameScale = 0.01f;
	//const float Game::sc_defaultZoom = 2.0f * sc_tiledToGameScale;

	void Game::spawnObjects()
	{
		SceneManager::Get();
	}

	void Game::applySceneView()
	{
		/*std::cout << "applySceneView called, zoom = "
			<< SceneManager::Get().sc_defaultZoom << "\n";*/

		std::cout<<"THE ZOOM : " << SceneManager::Get().sc_defaultZoom << std::endl;
		sf::View view = m_window.getDefaultView();

		float defaultWidth = view.getSize().x;
		float defaultHeight = view.getSize().y;

		view.zoom(SceneManager::Get().sc_defaultZoom);
		m_window.setView(view);

		float zoomX = defaultWidth / view.getSize().x;
		float zoomY = defaultHeight / view.getSize().y;

		std::cout << "Zoom applied: X=" << zoomX << " Y=" << zoomY << std::endl;

		std::cout << "YAAYYYY!" << std::endl;

	}

	Game::Game()
	{
		initWindow();
		initPhysics();
		initWeaponManager();
		spawnObjects();
		applySceneView();

	}

	Game::~Game()
	{
		WindowManager::clear();

		for (auto& obj : GameObject::s_gameObjects)
		{
			delete obj;
		}
		GameObject::s_gameObjects.clear();
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
				m_window.close();
			}

			if (sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::G)
			{

			}

			for (const auto& obj : GameObject::s_gameObjects)
			{
				if (auto player = dynamic_cast<Player*>(obj))
				{
					player->handleEvent(sfEvent);
				}
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
		for (auto* obj : GameObject::s_gameObjects)
		{
			obj->Awake();
		}
	}

	void Game::start()
	{
		for (auto* obj : GameObject::s_gameObjects)
		{
			obj->Start();
		}
	}

	void Game::render()
	{
		m_window.clear(sf::Color::Black);


		SceneManager::Get().renderSceneObjects(m_window);

		m_window.display();

	}

}