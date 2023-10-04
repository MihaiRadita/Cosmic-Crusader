#include<iostream>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Test");
	sf::Event e;

	while (window.isOpen())
	{
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
		}
	}

	system("PUASE");
	return 0;
}