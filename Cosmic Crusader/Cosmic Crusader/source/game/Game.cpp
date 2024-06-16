#include "stdafx.h"
#include "Game.h"

namespace ratchet
{
	Game::Game()
	{
		initWindow();
		initPhysics();
		initPlayer();
		initMap();

	}

	Game::~Game()
	{
		delete m_player;
		delete m_physics;
		delete m_ground;
		delete m_Wall;
	}

	void Game::initWindow()
	{
		m_window.create(sf::VideoMode(800, 600), "Cosmic Crusader", sf::Style::Titlebar | sf::Style::Close);
		m_window.setFramerateLimit(144);
	}

	void Game::initPlayer()
	{
		m_player = new Player();
	}

	void Game::initPhysics()
	{
		m_physics = new Physics();
	}

	void Game::initMap()
	{
		m_ground = new Tile();

		m_ground->init();

		m_ground->setScale(1.0f, 1.0f);
		m_ground->setPosition(20.f, 380.f);
		m_ground->initPhysics();

		m_Wall = new Tile();
		m_Wall->init();

		m_Wall->setScale(1.0f, 1.0f);
		m_Wall->setPosition(250.f, 150.f);
		m_Wall->initPhysics();
	}

	const sf::RenderWindow& Game::getWindow() const
	{
		return m_window;
	}

	void Game::handleEvents()
	{
		//player->resetControls();
		while (m_window.pollEvent(m_ev))
		{
			m_player->handleEvent(m_ev);
			if (m_ev.type == sf::Event::Closed)
			{
				m_window.close();
			}
			if (m_ev.type == sf::Event::KeyPressed && m_ev.key.code == sf::Keyboard::Escape)
			{
				m_window.close();
			}
		}
	}

	void Game::update()
	{
		handleEvents();

		updatePlayer();
		m_physics->update();

		//updateCollision();

#ifdef IS_RATCHET_DEBUG
		m_ground->printSpriteColliderTilePosition();
		m_player->printSpriteColliderPositionPlayer();
#endif
	}

	void Game::updatePlayer()
	{
		m_player->update();
	}

	void Game::updateCollision()
	{
		//Player collisions
		updatePlayerCollision();
	}

	void Game::updatePlayerCollision()
	{
		if (m_player->getBounds().left < 0.f)
		{
			m_player->setPosition(0.f, m_player->getBounds().top);
		}
		else if (m_player->getBounds().left + m_player->getBounds().width > m_window.getSize().x)
		{
			m_player->setPosition(m_window.getSize().x - m_player->getBounds().width, m_player->getBounds().top);
		}

		if (m_player->getBounds().top < 0.f)
		{
			m_player->setPosition(m_player->getBounds().left, 0.f);
		}
		else if (m_player->getBounds().top + m_player->getBounds().height > m_window.getSize().y)
		{
			m_player->setIsOnGround(true);
			m_player->setPosition(m_player->getBounds().left, m_window.getSize().y - m_player->getBounds().height);
		}
	}

	void Game::updateTile()
	{
		m_ground->update();
	}


	void Game::render()
	{
		m_window.clear(sf::Color::Black);

		renderPlayer();
		renderTile();

		m_window.display();
	}

	void Game::renderPlayer()
	{
		m_player->render(m_window);
	}

	void Game::renderTile()
	{
		m_ground->render(m_window);
		m_Wall->render(m_window);
	}
}