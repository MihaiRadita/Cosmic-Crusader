#include "stdafx.h"
#include "Game.h"

namespace ratchet
{
	void Game::spawnObjects()
	{
		{ 

			std::ifstream file("Textures/Levels/Level1/JsonFIles/LevelMap..tmj");

			if (!file.is_open())
			{
				std::cerr << "ERROR! The file could not be opened!" << std::endl;
			}
			
			nlohmann::json j;

			file >> j;
			file.close();

			nlohmann::json layer;

			for (const auto& l : j["layers"])
			{
				if (l["name"] == "Tile Objects")
				{
					layer = l;
#ifdef IS_RATCHET_DEBUG
					std::cout << "We have a match!" << std::endl;
#endif
					break;
				}
			}


			const auto& objects = layer["objects"];

			int coolideNumber = 0;

			for (const auto& obj : objects)
			{
				auto config = GameObjectConfig();
				config.m_Faction = FACTION_UNKNOWN;
				config.m_colliderType = COLLIDERTYPE_UNKNOWN;
				config.m_colliderShapeType = COLLIDERSHAPETYPE_UNKNOWN;
				config.m_movementType = MOVEMENTTYPE_UNKNOWN;

				config.positionXOffset = 0.f;
				config.positionYOffset = -64.f;

				config.position = sf::Vector2f(obj["x"].get<float>() + config.positionXOffset, obj["y"].get<float>() + config.positionYOffset);
				config.rotation = obj["rotation"];
				config.scale = sf::Vector2f(1.0f, 1.0f);
				config.startSpriteTexturePath = "D:/Long Gits/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/Levels/Level1/Tileset/";
				config.startSpriteTexturePathAddition = obj["name"].get<std::string>();
				config.startSpriteTexturePath = config.startSpriteTexturePath + config.startSpriteTexturePathAddition + ".png";

				auto colliderConfig = RectAngleColliderConfig();
				colliderConfig.m_layer = PhysiscsLayer::Platforms;
				colliderConfig.m_bodyDef.type = b2_staticBody;
				colliderConfig.m_bodyDef.fixedRotation = true;
				colliderConfig.m_fixtureDef.density = 0.f;
				colliderConfig.m_fixtureDef.friction = 90.f;
				colliderConfig.m_fixtureDef.restitution = 0.1f;


				config.m_colliderConfig = &colliderConfig;

				m_gameObjects.push_back(new GameObject(config));
			}

			

			/*auto config = GameObjectConfig();
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
			colliderConfig.m_fixtureDef.friction = 0.2f;
			colliderConfig.m_fixtureDef.restitution = 0.1f;


			config.m_colliderConfig = &colliderConfig;

			m_gameObjects.push_back(new GameObject(config));*/


		/*	auto config2 = GameObjectConfig();
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
			colliderConfig2.m_fixtureDef.friction = 0.2f;
			colliderConfig2.m_fixtureDef.restitution = 0.1f;


			config2.m_colliderConfig = &colliderConfig2;

			m_gameObjects.push_back(new GameObject(config2));


			auto config3 = GameObjectConfig();
			config3.m_Faction = FACTION_UNKNOWN;
			config3.m_colliderType = COLLIDERTYPE_UNKNOWN;
			config3.m_colliderShapeType = COLLIDERSHAPETYPE_UNKNOWN;
			config3.m_movementType = MOVEMENTTYPE_UNKNOWN;
				  
			config3.position = sf::Vector2f(450.f, 150.f);
			config3.rotation = 0.0f;
			config3.scale = sf::Vector2f(1.0f, 1.0f);
			config3.startSpriteTexturePath = "D:/Long Gits/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/Levels/Level1/Tileset/Platform.png";;

			auto colliderConfig3 = RectAngleColliderConfig();
			colliderConfig3.m_layer = PhysiscsLayer::Platforms;
			colliderConfig3.m_bodyDef.type = b2_staticBody;
			colliderConfig3.m_bodyDef.fixedRotation = true;
			colliderConfig3.m_fixtureDef.density = 0.f;
			colliderConfig3.m_fixtureDef.friction = 0.2f;
			colliderConfig3.m_fixtureDef.restitution = 0.1f;


			config3.m_colliderConfig = &colliderConfig3;

			m_gameObjects.push_back(new GameObject(config3));


			auto config4 = GameObjectConfig();
			config4.m_Faction = FACTION_UNKNOWN;
			config4.m_colliderType = COLLIDERTYPE_UNKNOWN;
			config4.m_colliderShapeType = COLLIDERSHAPETYPE_UNKNOWN;
			config4.m_movementType = MOVEMENTTYPE_UNKNOWN;
				  
			config4.position = sf::Vector2f(650.f, 150.f);
			config4.rotation = 0.0f;
			config4.scale = sf::Vector2f(1.0f, 1.0f);
			config4.startSpriteTexturePath = "D:/Long Gits/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/Levels/Level1/Tileset/Platform.png";;

			auto colliderConfig4 = RectAngleColliderConfig();
			colliderConfig4.m_layer = PhysiscsLayer::Platforms;
			colliderConfig4.m_bodyDef.type = b2_staticBody;
			colliderConfig4.m_bodyDef.fixedRotation = true;
			colliderConfig4.m_fixtureDef.density = 0.f;
			colliderConfig4.m_fixtureDef.friction = 0.2f;
			colliderConfig4.m_fixtureDef.restitution = 0.1f;


			config4.m_colliderConfig = &colliderConfig4;

			m_gameObjects.push_back(new GameObject(config4));*/

		}

		{
			auto config = CreatureConfig();
			config.m_Faction = PLAYER;
			config.m_movementType = GROUND;
			config.m_colliderType = DYNAMIC;
			config.m_colliderShapeType = RECTANGLE;

			config.positionXOffset = 0.f;
			config.positionYOffset = 0.f;

			config.position = sf::Vector2f(500.0f, 100.f);
			config.rotation = 0.0f;
			config.scale = sf::Vector2f(1.f, 1.f);

			config.m_movingSpeed =800.59f;
			config.m_jumpingSpeed = 5000.0f;
			config.m_fallingSpeed = 700.0f;



			config.startSpriteTexturePath = "D:/Long Gits/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/PlayerTextures/Player1Textures/IdleTextures/Idle1.png";
			config.spriteTexturePath = "D:/Long Gits/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/PlayerTextures/Player1Textures/";

			auto colliderConfig = RectAngleColliderConfig();
			colliderConfig.m_layer = PhysiscsLayer::Player;
			colliderConfig.m_bodyDef.type = b2_dynamicBody;
			colliderConfig.m_bodyDef.bullet = true;
			colliderConfig.m_bodyDef.fixedRotation = true;
			colliderConfig.m_fixtureDef.density = 1.f;
			colliderConfig.m_fixtureDef.friction = 80.f;
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
		m_window.create(sf::VideoMode(960,640), "Cosmic Crusader", sf::Style::Titlebar | sf::Style::Close);
		m_window.setFramerateLimit(200000);
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

		// Box2D Time Calculation
		// auto timePhysicsNow =
		// auto fixedDeltaTime =
		// timeBox2DLastFrame =

		// SFML Time Calculation
		float timeNow = gameTime.getElapsedTime().asSeconds();
		float deltaTime = (timeNow - timeLastFrame);
		timeLastFrame = timeNow;

		/*if (deltaTime > 1.0f / 2.0f) {
			deltaTime = 1.0f / 2.0f;  
		}*/

		m_physics->update(deltaTime);

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
#ifdef IS_RATCHET_DEBUG
			std::cout << "Rendering object at position: " << obj->getSprite().getPosition().x << ", " << obj->getSprite().getPosition().y << std::endl;
			std::cout << "Texture pointer: " <<obj->getSprite().getTexture() << std::endl;
#endif

			obj->render(m_window);
		}

		m_window.display();
	}

}