#pragma once

namespace ratchet
{
	class AudioManager
	{
	public:

		static void Initialize();


		static sf::SoundBuffer* GetSoundBuffer(const std::string& path);


		static void PlaySound(
			const std::string& path,
			float volume = 100.f,
			bool loop = false
		);



	private:

		static constexpr int MAX_SIMULTANEOUS_SOUNDS = 32;


		static std::unordered_map<std::string, sf::SoundBuffer> m_buffers;


		static std::vector<sf::Sound> m_soundPool;
	};
}


