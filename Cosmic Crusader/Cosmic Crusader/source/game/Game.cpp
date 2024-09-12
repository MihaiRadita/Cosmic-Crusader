#include "stdafx.h"
#include "Game.h"

namespace ratchet
{
	void Game::spawnObjects()
	{
		{
			auto config = GameObjectConfig();
			config.m_Faction = FACTION_UNKNOWN;
			config.m_colliderType = COLLIDERTYPE_UNKNOWN;
			config.m_colliderShapeType= COLLIDERSHAPETYPE_UNKNOWN;
			config.m_movementType = MOVEMENTTYPE_UNKNOWN;

			config.position = sf::Vector2f(20.f, 380.f);
			config.rotation = 0.0f;
			config.scale = sf::Vector2f(1.0f, 1.0f);
			config.startSpriteTexturePath = "D:/Long Gits/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/Levels/Level1/Tileset/Platform.png";

			auto colliderConfig = RectAngleColliderConfig();
			colliderConfig.m_layer = PhysiscsLayer::Platforms;
			colliderConfig.m_bodyDef.type = b2_staticBody;
			colliderConfig.m_bodyDef.fixedRotation = true;
			colliderConfig.m_fixtureDef.density = 0.f;
			colliderConfig.m_fixtureDef.friction = 0.3f;
			colliderConfig.m_fixtureDef.restitution = 0.f;


			config.m_colliderConfig = &colliderConfig;

			m_gameObjects.push_back(new GameObject(config));


			auto config2 = GameObjectConfig();
			config2.m_Faction = FACTION_UNKNOWN;
			config2.m_colliderType = COLLIDERTYPE_UNKNOWN;
			config2.m_colliderShapeType = COLLIDERSHAPETYPE_UNKNOWN;
			config2.m_movementType = MOVEMENTTYPE_UNKNOWN;

			config2.position = sf::Vector2f(250.f, 150.f);
			config2.rotation = 0.0f;
			config2.scale = sf::Vector2f(1.0f, 1.0f);
			config2.startSpriteTexturePath = "D:/Long Gits/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/Levels/Level1/Tileset/Platform.png";;

			auto colliderConfig2 = RectAngleColliderConfig();
			colliderConfig2.m_layer = PhysiscsLayer::Platforms;
			colliderConfig2.m_bodyDef.type = b2_staticBody;
			colliderConfig2.m_bodyDef.fixedRotation = true;
			colliderConfig2.m_fixtureDef.density = 0.f;
			colliderConfig2.m_fixtureDef.friction = 0.3f;
			colliderConfig2.m_fixtureDef.restitution = 0.f;


			config2.m_colliderConfig = &colliderConfig2;

			m_gameObjects.push_back(new GameObject(config2));
		}

		{
			auto config = CreatureConfig();
			config.m_Faction = PLAYER;
			config.m_movementType = GROUND;
			config.m_colliderType = DYNAMIC;
			config.m_colliderShapeType = RECTANGLE;

			config.position = sf::Vector2f(3.0f, 100.f);
			config.rotation = 0.0f;
			config.scale = sf::Vector2f(1.f, 1.f);

			config.m_movingSpeed = 3.5f;
			config.m_jumpingSpeed = 40.9f;
			config.m_fallingSpeed = 12.4f;

			config.startSpriteTexturePath = "D:/Long Gits/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/PlayerTextures/Player1Textures/IdleTextures/Idle1.png";
			config.spriteTexturePath = "D:/Long Gits/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/PlayerTextures/Player1Textures/";

			auto colliderConfig = RectAngleColliderConfig();
			colliderConfig.m_layer = PhysiscsLayer::Player;
			colliderConfig.m_bodyDef.type = b2_dynamicBody;
			colliderConfig.m_bodyDef.bullet = true;
			colliderConfig.m_bodyDef.fixedRotation = true;
			colliderConfig.m_fixtureDef.density = 1.f;
			colliderConfig.m_fixtureDef.friction = 0.3f;
			colliderConfig.m_fixtureDef.restitution = 0.f;

			config.m_colliderConfig = &colliderConfig;

			m_gameObjects.push_back(new Player(config));

		}
	}
	Game::Game()
	{
		initWindow();
		initPhysics();
		spawnObjects();

	}

	Game::~Game()
	{
		delete m_physics;

		for (auto& obj : m_gameObjects)
		{
			delete obj;
		}
		m_gameObjects.clear();
		
	}

	void Game::initWindow()
	{
		m_window.create(sf::VideoMode(800, 600), "Cosmic Crusader", sf::Style::Titlebar | sf::Style::Close);
		m_window.setFramerateLimit(144);
	}

	void Game::initPhysics()
	{
		m_physics = new Physics();
	}


	const sf::RenderWindow& Game::getWindow() const
	{
		return m_window;
	}

	void Game::handleEvents()
	{
		while (m_window.pollEvent(m_ev))
		{
			if (m_ev.type == sf::Event::Closed)
			{
				m_window.close();
			}
			if (m_ev.type == sf::Event::KeyPressed && m_ev.key.code == sf::Keyboard::Escape)
			{
				m_window.close();
			}
			for (const auto& obj : m_gameObjects) {
				if (auto player = dynamic_cast<Player*>(obj)) {
					player->handleEvent(m_ev);
				}
			}

		}
	}
	void Game::update()
	{
		handleEvents();

		//updatePlayer();
		m_physics->update();

		for (auto& obj : m_gameObjects)
		{
			obj->update();
		}
	}




	void Game::render()
	{
		m_window.clear(sf::Color::Black);

		for (auto* obj : m_gameObjects)
		{
			std::cout << "Rendering object at position: " << obj->getSprite().getPosition().x
				<< ", " << obj->getSprite().getPosition().y << std::endl;
			std::cout << "Texture pointer: " <<obj->getSprite().getTexture() << std::endl;

			obj->render(m_window);
		}

		m_window.display();
	}

}