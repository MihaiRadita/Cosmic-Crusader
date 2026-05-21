#pragma once


namespace ratchet
{
	class Bullet;

	class Weapon 
	{
	public:
		enum class TYPE { None = 0, Blaster, FireLauncher,BombLauncher, RocketLauncher,Enemy1Blaster,Enemy2Blaster,Enemy1BombLauncher,Enemy2BombLauncher, Count };

		static const char*  getWeaponTypeString(TYPE type)
		{
			switch (type)
			{
			case TYPE::None: return "None";
			case TYPE::Blaster: return "Blaster";
			case TYPE::FireLauncher: return "FireLauncher";
			case TYPE::RocketLauncher: return "RocketLauncher";
			case TYPE::Count: return "";
			case TYPE::Enemy1Blaster: return "Enemy1Blaster";
			case TYPE::Enemy2Blaster: return "Enemy2Blaster";
			case TYPE::Enemy2BombLauncher: return "Enemy2BombLauncher";
			}
		}

		Weapon();
		Weapon( const Weapon& weapon);


		TYPE m_weaponType;
		int m_currentAmmo;
		int m_maxAmmo;
		bool m_infiniteAmmo;
		int m_ammoDecrease;
		int m_WeaponID;
		int m_bulletID;

		float m_weaponDamage = 0.0f;

		bool m_facigRight = true;
		int m_bulletPoolIncrementation;

		static void ClearWeaponList();
		static void ClearBulletList();

		void DecreaseAmmo();

		//Weapon Sounds
		sf::SoundBuffer m_weaponSoundBuffer;
		sf::Sound m_weaponSound;

		float m_weaponSoundVolume;
		bool m_weaponSoundLoop;


		//Functions
		void Fire(const sf::Vector2f position, const float rotation, const sf::Vector2f direction, const bool facingRight);
		static void releaseBullet(Bullet* bulletToRelease);

	private:
		Bullet* findOrCreateBulletFromPool(const sf::Vector2f position, const float rotationDegrees, const bool orientation);

		static std::map<Weapon::TYPE, std::queue<Bullet*>> s_availableBulletList;
		static std::map<Weapon::TYPE, std::list<Bullet*>> s_inUseBulletList;
	};

	class WeaponAnimation
	{
	public:
		enum class STATE { Aim = 0, Recoil /*a.k.a. shoot*/, Count };
		static const char* getWeaponStateString(STATE state)
		{
			switch (state)
			{
			case STATE::Aim: return "Aim";
			case STATE::Recoil: return "Recoil";
			case STATE::Count: return "";
			}
		}

		enum class ANGLE { Angle0 = 0, Angle90, Angle45, AngleMinus45, Count };
		static const char* getWeaponAngleString(ANGLE angle)
		{
			switch (angle)
			{
			case ANGLE::Angle0: return "Angle0";
			case ANGLE::Angle90: return "Angle90";
			case ANGLE::Angle45: return "Angle45";
			case ANGLE::AngleMinus45: return "AngleMinus45";
			case ANGLE::Count: return "";
			}
		}
	};

}

