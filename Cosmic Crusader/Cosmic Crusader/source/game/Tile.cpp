#include "stdafx.h"

#include "Tile.h"



namespace ratchet
{
	Tile::Tile()
	{
	}

	Tile::Tile(const TileConfig& tileConfig) : GameObject(tileConfig)
	{
	}
}