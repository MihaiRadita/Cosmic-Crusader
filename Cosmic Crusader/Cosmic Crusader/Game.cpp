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
	delete this->player;
	delete this->physics;
	delete this->ground;
}

void Game::initWindow()
{
	this->window.create(sf::VideoMode(800, 600), "Cosmic Crusader", sf::Style::Titlebar | sf::Style::Close);
	this->window.setFramerateLimit(144);
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initPhysics()
{
	this->physics = new Physics();
}

void Game::initMap()
{
	this->ground = new Tile();

	this->ground->Init();
	this->ground->SetScale(0.4,0.4f);
	this->ground->SetPosition(180.f, this->window.getSize().y - this->ground->GetTileSprite().getGlobalBounds().height);
	this->ground->InitPhysics();
	
}

const sf::RenderWindow& Game::GetWindow() const
{
	return this->window;
}

void Game::handleEvents()
{
	//this->player->resetControls();
	while (this->window.pollEvent(this->ev))
	{
		this->player->handleEvent(this->ev);
		if (this->ev.type == sf::Event::Closed)
		{
			this->window.close();
		}
		if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
		{
			this->window.close();
		}
	}
}

void Game::update()
{
	this->handleEvents();

	this->updatePlayer();
	this->updatePhysics();
	this->updateCollision();
}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::updatePhysics()
{
	this->physics->update();
}

void Game::updateCollision()
{
	//Player collisions
	this->updatePlayerCollision();
}

void Game::updatePlayerCollision()
{
	if (this->player->getBounds().left < 0.f)
	{
		this->player->SetPosition(0.f, this->player->getBounds().top);
	}
	else if (this->player->getBounds().left + this->player->getBounds().width > this->window.getSize().x)
	{
		this->player->SetPosition(this->window.getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	if (this->player->getBounds().top < 0.f)
	{
		this->player->SetPosition(this->player->getBounds().left, 0.f);
	}
	else if (this->player->getBounds().top + this->player->getBounds().height > this->window.getSize().y)
	{
		this->player->setIsOnGround(true);
		this->player->SetPosition(this->player->getBounds().left, this->window.getSize().y - this->player->getBounds().height);
	}
}


void Game::render()
{
	this->window.clear(sf::Color::Black);

	this->renderPlayer();
	this->renderTile();

	this->window.display();
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::renderTile()
{
	this->ground->render(this->window);
}
