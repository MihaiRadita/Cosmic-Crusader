#pragma once

#include "GameObject.h"

namespace ratchet
{
	class Tile : public GameObject
	{
	private:
	public:
		Tile();
		Tile(const TileConfig& tileConfig);
	};
}