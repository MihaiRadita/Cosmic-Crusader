#include "stdafx.h"

#include "Game.h"

int main()
{
	Game game;

	while (game.GetWindow().isOpen())
	{
		game.update();
		game.render();
	}

	return 0;
}