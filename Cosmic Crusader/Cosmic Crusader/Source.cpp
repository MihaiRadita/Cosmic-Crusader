#include "stdafx.h"

#include "Game.h"

int main()
{
	Game* game = new Game();

	while (game->GetWindow().isOpen())
	{
		game->update();
		game->render();
	}

	if (!game->GetWindow().isOpen())
	{
		delete game;
	}

	system("PAUSE");
	return 0;
}