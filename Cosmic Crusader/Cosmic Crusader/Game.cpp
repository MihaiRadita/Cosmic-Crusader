#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	this->initWindow();
	this->initPlayer();
	this->initPhysics();
	this->initMap();
	
}

Game::~Game()
{
	delete this->m_player;
	delete this->m_physics;
	delete this->m_ground;
}

void Game::initWindow()
{
	this->m_window.create(sf::VideoMode(800, 600), "Cosmic Crusader", sf::Style::Titlebar | sf::Style::Close);
	this->m_window.setFramerateLimit(144);
}

void Game::initPlayer()
{
	this->m_player = new Player();
}

void Game::initPhysics()
{
	this->m_physics = new Physics();
}

void Game::initMap()
{
	this->m_ground = new Tile();

	this->m_ground->init();

	this->m_ground->setScale(1.0f, 1.0f);
	this->m_ground->setPosition(30.f, 380.f);
	this->m_ground->initPhysics();
}

const sf::RenderWindow& Game::getWindow() const
{
	return this->m_window;
}

void Game::handleEvents()
{
	//this->player->resetControls();
	while (this->m_window.pollEvent(this->m_ev))
	{
		this->m_player->handleEvent(this->m_ev);
		if (this->m_ev.type == sf::Event::Closed)
		{
			this->m_window.close();
		}
		if (this->m_ev.type == sf::Event::KeyPressed && this->m_ev.key.code == sf::Keyboard::Escape)
		{
			this->m_window.close();
		}
	}
}

void Game::update()
{
	this->handleEvents();

	this->updatePlayer();
	this->updatePhysics();

	//this->updateCollision();

	this->m_ground->printSpriteColliderTilePosition();
	this->m_player->printSpriteColliderPositionPlayer();
}

void Game::updatePlayer()
{
	this->m_player->update();
}

void Game::updatePhysics()
{
	this->m_physics->update();
}

void Game::updateCollision()
{
	//Player collisions
	this->updatePlayerCollision();
}

void Game::updatePlayerCollision()
{
	if (this->m_player->getBounds().left < 0.f)
	{
		this->m_player->setPosition(0.f, this->m_player->getBounds().top);
	}
	else if (this->m_player->getBounds().left + this->m_player->getBounds().width > this->m_window.getSize().x)
	{
		this->m_player->setPosition(this->m_window.getSize().x - this->m_player->getBounds().width, this->m_player->getBounds().top);
	}

	if (this->m_player->getBounds().top < 0.f)
	{
		this->m_player->setPosition(this->m_player->getBounds().left, 0.f);
	}
	else if (this->m_player->getBounds().top + this->m_player->getBounds().height > this->m_window.getSize().y)
	{
		this->m_player->setIsOnGround(true);
		this->m_player->setPosition(this->m_player->getBounds().left, this->m_window.getSize().y - this->m_player->getBounds().height);
	}
}

void Game::updateTile()
{
	this->m_ground->update();
}


void Game::render()
{
	this->m_window.clear(sf::Color::Black);

	this->renderPlayer();
	this->renderTile();

	this->m_window.display();
}

void Game::renderPlayer()
{
	this->m_player->render(this->m_window);
}

void Game::renderTile()
{
	this->m_ground->render(this->m_window);
}
