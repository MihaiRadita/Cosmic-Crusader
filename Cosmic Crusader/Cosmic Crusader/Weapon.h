#pragma once

//#include "GameObject.h"


namespace ratchet
{

	class Weapon 
	{
	public:
		enum class TYPE { None = 0, Blaster, FireLauncher, RocketLauncher,Enemy1Blaster, Count };

		static const char*  getWeaponTypeString(TYPE type)
		{
			switch (type)
			{
			case TYPE::None: return "None";
			case TYPE::Blaster: return "Blaster";
			case TYPE::FireLauncher: return "FireLauncher";
			case TYPE::RocketLauncher: return "RocketLauncher";
			case TYPE::Count: return "";
			}
		}

		Weapon();
		Weapon( const Weapon& weapon);


		TYPE m_weaponType;
		int m_currentAmmo;
		std::string m_WeaponID;

		void Fire(const sf::Vector2f &positon,const float& rotation, const float& direction);

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

