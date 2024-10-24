#include "stdafx.h"
#include "Game.h"

namespace ratchet
{
	static constexpr auto sc_tiledToGameScale = 0.01f;
	static constexpr auto sc_defaultZoom = 2.0f * sc_tiledToGameScale;

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
					//std::cout << "We have a match!" << std::endl;
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

				config.scale = sf::Vector2f(1.0f, 1.0f) * sc_tiledToGameScale;

				float tileWidth = 64.0f;
				float tileHeight = 64.0f;

				config.positionXOffset = 0.f;
				config.positionYOffset =  -tileHeight * config.scale.y;


				float posX = obj["x"].get<float>() * config.scale.x;
				float posY = obj["y"].get<float>() * config.scale.y;

				posY += config.positionYOffset;


				config.position = sf::Vector2f(posX, posY);
				config.rotation = obj["rotation"];
				config.startSpriteTexturePath = "D:/Long Gits/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/Levels/Level1/Tileset/";
				config.startSpriteTexturePathAddition = obj["name"].get<std::string>();
				config.startSpriteTexturePath = config.startSpriteTexturePath + config.startSpriteTexturePathAddition + ".png";

				auto colliderConfig = RectAngleColliderConfig();
				colliderConfig.m_layer = PhysiscsLayer::Platforms;
				colliderConfig.m_bodyDef.type = b2_staticBody;
				colliderConfig.m_bodyDef.fixedRotation = true;
				colliderConfig.m_fixtureDef.density = 0.0f;
				colliderConfig.m_fixtureDef.friction = 1.0f;
				colliderConfig.m_fixtureDef.restitution = 0.0f;


				config.m_colliderConfig = &colliderConfig;

				GameObject::s_gameObjects.push_back(new GameObject(config));
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

			config.position = sf::Vector2f(0.0f, 0.0f);
			config.rotation = 0.0f;
			config.scale = sf::Vector2f(1.0f, 1.0f) * sc_tiledToGameScale;

			config.m_movingSpeed = 7.0f;
			config.m_jumpImpulse = -10.0f;
			config.m_fallingSpeed = 7000.0f;



			config.startSpriteTexturePath = "D:/Long Gits/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/PlayerTextures/Player1Textures/IdleTextures/Idle1.png";
			config.spriteTexturePath = "D:/Long Gits/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/PlayerTextures/Player1Textures/";

			auto colliderConfig = RectAngleColliderConfig();
			colliderConfig.m_layer = PhysiscsLayer::Player;
			colliderConfig.m_bodyDef.type = b2_dynamicBody;
			colliderConfig.m_bodyDef.bullet = true;
			colliderConfig.m_bodyDef.fixedRotation = true;
			colliderConfig.m_fixtureDef.density = 1.f;
			colliderConfig.m_fixtureDef.friction = 2.9f;
			colliderConfig.m_fixtureDef.restitution = 0.f;

			config.m_colliderConfig = &colliderConfig;

			GameObject::s_gameObjects.push_back(new Player(config));

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

		for (auto& obj : GameObject::s_gameObjects)
		{
			delete obj;
		}
		GameObject::s_gameObjects.clear();
		
	}

	void Game::initWindow()
	{
		m_window.create(sf::VideoMode(1280,720), "Cosmic Crusader", sf::Style::Titlebar | sf::Style::Close);
		// m_window.setFramerateLimit(60);

		sf::View view = m_window.getView();
		view.zoom(sc_defaultZoom);
		m_window.setView(view);
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

		// Box2D Time Calculation
		// auto timePhysicsNow =
		// auto fixedDeltaTime =
		// timeBox2DLastFrame =

		// SFML Time Calculation
		float timeNow = gameTime.getElapsedTime().asSeconds();
		float deltaTime = (timeNow - timeLastFrame);
		timeLastFrame = timeNow;

		if (deltaTime > 1.0f / 5.0f) {
			deltaTime = 1.0f / 5.0f;  
		}

		float timeStep = 1.0f / 120.0f;  
		float accumulatedTime = 0.0f;

		accumulatedTime += deltaTime;


		int maxSteps = 60;  
		int steps = 0;

		/*while (accumulatedTime > timeStep && steps < maxSteps)
		{
			accumulatedTime -= timeStep;
			steps++;
		}*/
			m_physics->update(timeStep);

		if (steps == maxSteps) {

			accumulatedTime = 0.0f;
		}


		for (auto& obj : GameObject::s_gameObjects)
		{
			obj->update();
		}

	}




	void Game::render()
	{
		m_window.clear(sf::Color::Black);

		for (auto* obj : GameObject::s_gameObjects)
		{
#ifdef IS_RATCHET_DEBUG
			//std::cout << "Rendering object at position: " << obj->getSprite().getPosition().x << ", " << obj->getSprite().getPosition().y << std::endl;
			//std::cout << "Texture pointer: " <<obj->getSprite().getTexture() << std::endl;
#endif

			if (auto player = dynamic_cast<Player*>(obj))
			{
				sf::View view = m_window.getView();
				view.setCenter(player->getCollider()->getBody()->GetPosition().x, player->getCollider()->getBody()->GetPosition().y);
				m_window.setView(view);
			}

			obj->render(m_window);
		}

		m_window.display();
	}

}