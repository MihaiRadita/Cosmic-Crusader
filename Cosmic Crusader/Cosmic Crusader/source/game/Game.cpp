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
				colliderConfig.m_fixtureDef.friction = 76.f;
				colliderConfig.m_fixtureDef.restitution = 0.01f;


				config.m_colliderConfig = &colliderConfig;

				GameObject::s_gameObjects.push_back(new GameObject(config));
			}
		}

		{
			auto config = CreatureConfig();
			config.m_Faction = PLAYER;
			config.m_movementType = GROUND;
			config.m_colliderType = DYNAMIC;
			config.m_colliderShapeType = RECTANGLE;

			config.positionXOffset = 0.f;
			config.positionYOffset = 0.f;

			config.position = sf::Vector2f(5.0f, 0.0f);
			config.rotation = 0.0f;
			config.scale = sf::Vector2f(1.0f, 1.0f) * sc_tiledToGameScale;

			config.m_movingSpeed = 7.0f;
			config.m_jumpImpulse = -10.0f;
			config.m_fallingSpeed = 7000.0f;

			config.startSpriteTexturePath = "D:/Long Gits/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/PlayerTextures/Player1Textures/IdleTextures/None/Idle1.png";
			config.spriteTexturePath = "D:/Long Gits/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/PlayerTextures/Player1Textures/";
			config.fallingSpriteTexturePath = "D:/Long gits/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/PlayerTextures/Player1Textures/JumpTextures/None/Jump7.png";

			auto colliderConfig = CapsuleColliderConfig();
			colliderConfig.m_layer = PhysiscsLayer::Player;
			colliderConfig.m_bodyDef.type = b2_dynamicBody;
			colliderConfig.m_bodyDef.bullet = true;
			colliderConfig.m_bodyDef.fixedRotation = true;
			colliderConfig.m_fixtureDef.density = 1.0f;
			colliderConfig.m_fixtureDef.friction = 0.0f;
			colliderConfig.m_fixtureDef.restitution = 0.f;
			colliderConfig.m_height = 1.13f;
			colliderConfig.m_radius = 0.25f;

		
			config.m_colliderConfig = &colliderConfig;

			// fie este un std::vector<Weapon::TYPE>, fie este un std::map<Weapon::TYPE, bool>
			config.m_usableWeaponTypeList = { {Weapon::TYPE::None, true}, {Weapon::TYPE::Blaster, true}, {Weapon::TYPE::FireLauncher, true}, {Weapon::TYPE::RocketLauncher, true} }; // ce arme POATE folosi

			config.m_currentAngle = WeaponAnimation::ANGLE::Angle0;
			config.m_currentState = WeaponAnimation::STATE::Aim;
			config.m_currentWeaponType = Weapon::TYPE::None;

			// std::vector<std::pair<Weapon::Type, std::optional<WeaponConfig>>>
			config.m_weaponConfigList = // reprezinta ce arme ai in inventar deja
			{
				std::make_pair(Weapon::TYPE::Blaster, WeaponConfig(51)),
				std::make_pair(Weapon::TYPE::RocketLauncher, WeaponConfig(12)),
				std::make_pair(Weapon::TYPE::Blaster, WeaponConfig(2401)),
				std::make_pair(Weapon::TYPE::FireLauncher, std::nullopt),

			};
			config.m_currentlyEquippedWeaponIndex = 1;

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

				sf::Sprite sprite = player->getSprite();
			}

			obj->render(m_window);
		}
		m_window.display();

	}

}