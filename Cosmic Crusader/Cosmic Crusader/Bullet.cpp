#include "stdafx.h"
#include "Bullet.h"

ratchet::Bullet::Bullet()
{
}

ratchet::Bullet::Bullet(const BulletConfig& config) : GameObject(config)
{
	m_damage = config.m_damage;
	m_ammo = config.m_ammo;
}

ratchet::Bullet::~Bullet()
{
}
