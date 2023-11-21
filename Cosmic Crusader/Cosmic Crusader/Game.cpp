#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	this->initWindow();
	this->initPlayer();
	
}

Game::~Game()
{
	delete this->player;
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

const sf::RenderWindow& Game::GetWindow() const
{
	return this->window;
}

void Game::update()
{
	while (this->window.pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
		{
			this->window.close();
		}
		if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
		{
			this->window.close();
		}
	}

	this->updatePlayer();
	this->updateCollision();
}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateCollision()
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
		this->player->SetPosition(this->player->getBounds().left, this->window.getSize().y - this->player->getBounds().height);
	}
}

void Game::render()
{
	this->window.clear(sf::Color::Black);

	this->renderPlayer();

	this->window.display();
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}
