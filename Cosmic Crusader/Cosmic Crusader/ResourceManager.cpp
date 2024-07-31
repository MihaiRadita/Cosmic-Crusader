#include "stdafx.h"
#include "ResourceManager.h"

sf::Texture ratchet::ResourceManager::findOrFetchTexture(std::string texturePath)
{
    auto loadedTextureIterator = m_loadedTextures.find(texturePath);

    if (loadedTextureIterator != m_loadedTextures.end())
    {
        return loadedTextureIterator->second;
    }
    else
    {
        sf::Texture texture;

        if (!texture.loadFromFile(texturePath))
        {
            std::cout << "The Texture path was not found";
            return sf::Texture();
        }
        else
        {
            auto emplaceTexture = m_loadedTextures.emplace(texturePath, std::move(texture));

            return emplaceTexture.first->second;
        }
    }
}
