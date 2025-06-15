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
					TRACE_CHANNEL(TR_GAMEOBJECT_INIT, "We have a match!");
					break;
				}
			}


			const auto& objects = layer["objects"];

			int coolideNumber = 0;

			for (const auto& obj : objects)
			{
				auto config = GameObjectConfig();
				config.m_Faction = Faction::FACTION_UNKNOWN;
				config.m_colliderType = COLLIDERTYPE_UNKNOWN;
				config.m_colliderShapeType = COLLIDERSHAPETYPE_UNKNOWN;
				config.m_movementType = MovementType::MOVEMENTTYPE_UNKNOWN;

				config.scale = sf::Vector2f(1.0f, 1.0f) * sc_tiledToGameScale;

				float tileWidth = 64.0f;
				float tileHeight = 64.0f;

				config.positionXOffset = 0.f;
				config.positionYOffset = -tileHeight * config.scale.y;


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
				colliderConfig.m_fixtureDef.isSensor = false;


				config.m_colliderConfig = &colliderConfig;

				GameObject::s_gameObjects.push_back(new GameObject(config));
			}
		}

		{
			auto config = WeaponConfig(51, 12, true, 0.5f, 0.4f);
			config.m_movementType = MovementType::MOVEMENTTYPE_UNKNOWN;
			config.m_Faction = Faction::FACTION_UNKNOWN;
			config.m_colliderType = COLLIDERTYPE_UNKNOWN;
			config.m_colliderShapeType = COLLIDERSHAPETYPE_UNKNOWN;
			config.m_weaponType = Weapon::TYPE::Blaster;

			float tileWidth = 64.0f;
			float tileHeight = 64.0f;

			config.positionXOffset = 0.f;
			config.positionYOffset = 0.f;

			config.position = sf::Vector2f(18.0f, 4.8f);
			config.rotation = 0.0f;
			config.scale = sf::Vector2f(1.0f, 1.0f) * sc_tiledToGameScale;

			config.startSpriteTexturePath = "D:/Long Gits/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/Levels/Level1/Objects/Weapons/Player/Blaster1.png";

			auto colliderConfig = RectAngleColliderConfig();
			colliderConfig.m_layer = PhysiscsLayer::Items;
			colliderConfig.m_bodyDef.type = b2_staticBody;
			colliderConfig.m_bodyDef.fixedRotation = true;
			colliderConfig.m_fixtureDef.density = 0.0f;
			colliderConfig.m_fixtureDef.friction = 0.0f;
			colliderConfig.m_fixtureDef.restitution = 0.0f;
			colliderConfig.m_fixtureDef.isSensor = true;


			TRACE_CHANNEL(TR_COLLISION, "IS SENSOR : " << colliderConfig.m_fixtureDef.isSensor);

			config.m_colliderConfig = &colliderConfig;

			GameObject::s_gameObjects.push_back(new WeaponPickup(config));

		}

		{
			auto config = CreatureConfig();
#ifdef IS_RATCHET_DEBUG
			config.m_debugDraw = true;
#endif

			config.m_Faction = Faction::PLAYER;
			config.m_movementType = MovementType::GROUND;
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
			config.m_AngleBase = 45.f;

			config.startSpriteTexturePath = "D:/Long Gits/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/PlayerTextures/Player1Textures/IdleTextures/None/Idle1.png";
			config.spriteTexturePath = "D:/Long Gits/Cosmic-Crusader/Cosmic Crusader/Cosmic Crusader/Textures/PlayerTextures/Player1Textures/";

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
			colliderConfig.m_fixtureDef.isSensor = false;
#ifdef IS_RATCHET_DEBUG
			colliderConfig.m_debugDraw = false;
#endif


			config.m_colliderConfig = &colliderConfig;

			// fie este un std::vector<Weapon::TYPE>, fie este un std::map<Weapon::TYPE, bool>
			config.m_usableWeaponTypeList = { {Weapon::TYPE::None, true}, {Weapon::TYPE::Blaster, false}, {Weapon::TYPE::FireLauncher, false}, {Weapon::TYPE::RocketLauncher, false} }; // ce arme POATE folosi

			config.m_currentAngle = WeaponAnimation::ANGLE::Angle0;
			config.m_currentState = WeaponAnimation::STATE::Aim;

			config.m_characterAngles = { WeaponAnimation::ANGLE::Angle0,WeaponAnimation::ANGLE::Angle45, WeaponAnimation::ANGLE::Angle90,WeaponAnimation::ANGLE::AngleMinus45 };

			config.m_weaponTypeList = { Weapon::TYPE::None, Weapon::TYPE::Blaster, Weapon::TYPE::FireLauncher, Weapon::TYPE::RocketLauncher };

			config.m_bodShoulderOffset = 0.4f;

			// std::vector<std::pair<Weapon::Type, std::optional<WeaponConfig>>>
			config.m_initialWeaponConfigList = // reprezinta ce arme ai in inventar deja
			{
				std::make_pair(Weapon::TYPE::None, std::nullopt),
			};

			config.m_currentWeaponType = config.m_initialWeaponConfigList[0].first;

			config.m_currentlyEquippedWeaponIndex = 0;

			GameObject::s_gameObjects.push_back(new Player(config));

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
		float timeNow = gameTime.getElapsedTime().asSeconds();
		float deltaTime = (timeNow - timeLastFrame);
		timeLastFrame = timeNow;

		sf::Vector2i newMousePos = sf::Mouse::getPosition(m_window);

		if (currenmousePosition != newMousePos)
		{
			currenmousePosition = newMousePos;
			TRACE_CHANNEL(TR_MOUSE, "Mouse Position: " << currenmousePosition.x << ", " << currenmousePosition.y << " !");

			sf::Vector2f newMouseWorld = m_window.mapPixelToCoords(currenmousePosition);

			TRACE_CHANNEL(TR_MOUSE, "Mouse Position in Wolrd: " << newMouseWorld.x << ", " << newMouseWorld.y << "!");
		}

		if (deltaTime > 1.0f / 5.0f) {
			deltaTime = 1.0f / 5.0f;
		}

		float timeStep = 1.0f / 120.0f;
		float accumulatedTime = 0.0f;

		accumulatedTime += deltaTime;

		int maxSteps = 60;
		int steps = 0;

		Physics::update(timeStep);

		if (steps == maxSteps) {

			accumulatedTime = 0.0f;
		}

		for (auto& obj : GameObject::s_gameObjects)
		{
			obj->update();
		}

		//sf::Mouse::setPosition(sf::Vector2i(20, 20), m_window);

	}

	void Game::render()
	{
		m_window.clear(sf::Color::Black);

		for (auto* obj : GameObject::s_gameObjects)
		{
			TRACE_CHANNEL(TR_RENDERING, "Rendering object at position: " << obj->getSprite().getPosition().x << ", " << obj->getSprite().getPosition().y << std::endl);
			TRACE_CHANNEL(TR_RENDERING, "Texture pointer: " <<obj->getSprite().getTexture() << std::endl);

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