#include "stdafx.h"
#include "ResourceManager.h"


namespace ratchet {
    ResourceManager* ResourceManager::getInstance()
    {
        if (!m_resourceManager)
        {
            m_resourceManager = new ResourceManager();
        }

        return m_resourceManager;

    }
    const sf::Texture* ratchet::ResourceManager::findOrFetchTexture(std::string& texturePath)
    {
        const auto& loadedTextureIterator = m_loadedTextures.find(texturePath);
        if (loadedTextureIterator != m_loadedTextures.end())
        {
            return &loadedTextureIterator->second;
        }
        else
        {
            sf::Texture texture;

            if (!texture.loadFromFile(texturePath))
            {
    #ifdef IS_RATCHET_DEBUG
                std::cout << "The Texture path was not found";
    #endif
                return nullptr;
            }
            else
            {
                m_loadedTextures.emplace(texturePath, std::move(texture));
                return &m_loadedTextures[texturePath];
            }
        }
    }

    ResourceManager::ResourceManager()
    {

    }

    ResourceManager::~ResourceManager()
    {
        if (m_resourceManager != nullptr)
        {
            delete m_resourceManager;
            m_resourceManager = nullptr;
        }
    }
    
    ResourceManager* ResourceManager::m_resourceManager = nullptr;
   
}


