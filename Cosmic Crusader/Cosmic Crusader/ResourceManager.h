#pragma once

namespace ratchet
{
	class ResourceManager
	{
		sf::Texture findOrFetchTexture(std::string texturePath);
		std::map<std::string, sf::Texture> m_loadedTextures;
		sf::Texture FindTextureInList(std::string texturePath);
	};


}

