#include "stdafx.h"

#include "game/Game.h"

int main()
{
	ratchet::Game* game = new ratchet::Game();

	game->awake();
	game->start();

	while (game->getWindow().isOpen())
	{
		game->update();
		game->render();
	}

	delete game;

	system("PAUSE");
	return 0;
}