#include "stdafx.h"
#include "Bullet.h"



namespace ratchet
{
	Bullet::Bullet()
	{
	}

	Bullet::Bullet(const BulletConfig& config) : GameObject(config)
	{
		m_damage = config.m_damage;
		m_ammo = config.m_ammo;
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::update()
	{

	}
}

