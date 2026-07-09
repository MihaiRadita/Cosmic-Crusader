#include "stdafx.h"
#include "AudioManager.h"

namespace ratchet
{
	std::unordered_map<std::string, sf::SoundBuffer> AudioManager::m_buffers;


	std::vector<sf::Sound> AudioManager::m_soundPool;



	void AudioManager::Initialize()
	{
		m_soundPool.resize(MAX_SIMULTANEOUS_SOUNDS);
	}



	sf::SoundBuffer* AudioManager::GetSoundBuffer(const std::string& path)
	{
		auto it = m_buffers.find(path);


		if (it != m_buffers.end())
		{
			return &it->second;
		}



		sf::SoundBuffer buffer;


		if (!buffer.loadFromFile(path))
		{
			std::cout
				<< "Cannot load sound: "
				<< path
				<< std::endl;

			return nullptr;
		}



		auto result = m_buffers.emplace(
			path,
			std::move(buffer)
		);



		return &result.first->second;
	}





	void AudioManager::PlaySound(
		const std::string& path,
		float volume,
		bool loop
	)
	{
		sf::SoundBuffer* buffer = GetSoundBuffer(path);


		if (!buffer)
			return;



		for (auto& sound : m_soundPool)
		{
			if (sound.getStatus() != sf::Sound::Playing)
			{
				sound.setBuffer(*buffer);

				sound.setVolume(volume);

				sound.setLoop(loop);

				sound.play();

				return;
			}
		}

	}
}