#pragma once

namespace ratchet
{
	class ResourceManager
	{
	public:
		ResourceManager(const ResourceManager*) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;

		static ResourceManager* getInstance();
		

		const sf::Texture* findOrFetchTexture(std::string& texturePath);
		std::map<std::string, sf::Texture> m_loadedTextures;

	private:
		ResourceManager();
		~ResourceManager();
		static ResourceManager* m_resourceManager;
	};


}

