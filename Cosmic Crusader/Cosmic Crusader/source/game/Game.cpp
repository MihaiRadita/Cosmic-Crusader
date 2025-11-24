#include "stdafx.h"
#include "Game.h"
#include "TileConfig.h"

#include "EnumMask.h"

namespace ratchet
{
	const float Game::sc_tiledToGameScale = 0.01f;
	const float Game::sc_defaultZoom = 2.0f * sc_tiledToGameScale;

	void Game::spawnObjects()
	{
		{
			std::ifstream file("Textures/Levels/Level1/JsonFIles/LevelMap.tmj");

			if (!file.is_open())
			{
				TRACE_CHANNEL("WARNING", "ERROR! The file could not be opened!");
			}

			nlohmann::json jsonFile;

			file >> jsonFile;
			file.close();
			
			// Deserialise from file.
			for (const auto& layer : jsonFile["layers"])
			{
				const auto& validLayer = layer.contains("objects");
				if (!validLayer) continue;

				const auto& layerName = layer["name"].get<std::string>();
				for (const auto& obj : layer["objects"])
				{
					bool succeeded = false;
					if (layerName == "Tile Objects")
					{
						auto config = TileConfig();
						if (config.deserialise(obj))
						{
							GameObject::s_gameObjects.push_back(new Tile(config));
							succeeded = true;
						}
					}
					else if (layerName == "Player")
					{
						auto config = CreatureConfig();
#ifdef IS_RATCHET_DEBUG
						config.m_debugDraw = true;
#endif
						if (config.deserialise(obj))
						{
#ifdef IS_RATCHET_DEBUG
							config.m_colliderConfig->m_debugDraw = false;
#endif
							GameObject::s_gameObjects.push_back(new Player(config));
							succeeded = true;
						}
					}
					else if (layerName == "Enemies")
					{
						auto config = SelfControlledCreatureConfig();
#ifdef IS_RATCHET_DEBUG
						config.m_debugDraw = true;
#endif
						if (config.deserialise(obj))
						{
#ifdef IS_RATCHET_DEBUG
							config.m_colliderConfig->m_debugDraw = false;
#endif
							GameObject::s_gameObjects.push_back(new SelfControlledCreature(config));
							succeeded = true;
						}
					}
					else if (layerName == "Weapons Bullets")
					{
						auto config = BulletConfig();
						if (config.deserialise(obj))
						{
							PrefabAssets::Get().RegisterBulletConfig(config.m_objectID, &config);
							succeeded = true;
						}
					}
					else if (layerName == "Weapons")
					{
						auto config = WeaponConfig(0.0f, 0.0f, true);
						if (config.deserialise(obj))
						{
							if (obj["type"] == "Weapon Pickup")
							{
								GameObject::s_gameObjects.push_back(new WeaponPickup(config));
							}

							PrefabAssets::Get().RegisterWeaponConfig(config.m_objectID, &config);
							succeeded = true;
						}
					}

					if(!succeeded)
					{
						TRACE_CHANNEL("GAMEOBJECT_INIT", "FAILED to deserialise tile.");
					}
				}
			}
		}
	}

	Game::Game()
	{
		initWindow();
		initPhysics();
		initWeaponManager();
		spawnObjects();

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

		sf::View view = m_window.getView();
		view.zoom(sc_defaultZoom);
		m_window.setView(view);
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

		// SFML Time Calculation
		sf::Vector2i newMousePos = sf::Mouse::getPosition(m_window);

		if (currenmousePosition != newMousePos)
		{
			currenmousePosition = newMousePos;
			TRACE_CHANNEL("MOUSE", "Mouse Position: ", currenmousePosition.x, ", ", currenmousePosition.y, " !");

			sf::Vector2f newMouseWorld = m_window.mapPixelToCoords(currenmousePosition);

			TRACE_CHANNEL("MOUSE", "Mouse Position in Wolrd: ", newMouseWorld.x, ", ", newMouseWorld.y, "!");
		}

		float timeStep = 1.0f / 120.0f;

		Physics::update(timeStep);

		for (auto i = 0u; i < GameObject::s_gameObjects.size(); i++)
		{
			if (auto obj = GameObject::s_gameObjects[i])
			{
				obj->update();
			}
			else
			{
				TRACE_CHANNEL("GAME_OBJECT", "Cannot update null game object of index [", i, "].");
			}
		}

		GameObject::clearQueuedObjectsToDestroy();

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

		for (auto* obj : GameObject::s_gameObjects)
		{
			TRACE_CHANNEL("RENDERING", "Rendering object at position: ", obj->getSprite().getPosition().x, ", ", obj->getSprite().getPosition().y);
			TRACE_CHANNEL("RENDERING", "Texture pointer: ", obj->getSprite().getTexture());

			if (auto player = dynamic_cast<Player*>(obj))
			{
				sf::View view = m_window.getView();
				view.setCenter(player->getCollider()->getBody()->GetPosition().x, player->getCollider()->getBody()->GetPosition().y);
				m_window.setView(view);

				sf::Sprite sprite = player->getSprite();
			}

			obj->render(m_window);
		}
		m_window.display();

	}

}