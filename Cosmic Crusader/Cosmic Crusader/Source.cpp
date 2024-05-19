#include "stdafx.h"

#include "Game.h"

int main()
{
	Game* game = new Game();

	while (game->getWindow().isOpen())
	{
		game->update();
		game->render();
	}

	if (!game->getWindow().isOpen())
	{
		delete game;
	}

	system("PAUSE");
	return 0;
}