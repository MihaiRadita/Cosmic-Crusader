#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	this->initWindow();
}

void Game::initWindow()
{
	this->window.create(sf::VideoMode(800, 600), "Cosmic Crusader", sf::Style::Titlebar | sf::Style::Close);
	this->window.setFramerateLimit(144);
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
}

void Game::render()
{
	this->window.clear(sf::Color::Black);

	this->window.display();
}
