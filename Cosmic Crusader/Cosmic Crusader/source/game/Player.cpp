#include "stdafx.h"
#include "Player.h"

namespace ratchet
{
	void Player::destroyPlayerAnimations()
	{

	}

	Player::Player(const CreatureConfig& config) : Creature(config)
	{
		initVariables();
	}

	void Player::initVariables()
	{
		m_gravity = 0.090f;
		m_isMoving = false;
	}

	void Player::handleEvent(sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
		{
			sf::Keyboard::Key key = event.key.code;

			switch (key)
			{
			case sf::Keyboard::A:
				if (m_input.x >= 0) m_input.x = -1;
				break;
			case sf::Keyboard::D:
				if (m_input.x <= 0) m_input.x = +1;
				break;
			case sf::Keyboard::Space:
				m_input.isJump = true;
				break;
			default:
				break;
			}
			if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9)
			{
				if (!m_ownedWeaponList.empty())
				{
					int requestedIndex = key - sf::Keyboard::Num0;

					if (requestedIndex < m_ownedWeaponList.size())
					{
						Weapon::TYPE type = m_ownedWeaponList[requestedIndex]->m_weaponType;
						if (isWeaponAccessible(type))
						{
							m_input.weaponInputIndex = requestedIndex;
						}
						else
						{
							bool found = false;
							for (int i = requestedIndex + 1; i < m_ownedWeaponList.size(); ++i)
							{
								Weapon::TYPE t = m_ownedWeaponList[i]->m_weaponType;
								if (isWeaponAccessible(t))
								{
									m_input.weaponInputIndex = i;
									found = true;
									break;
								}
							}

							if (!found)
							{
								for (int i = 0; i < requestedIndex; ++i)
								{
									Weapon::TYPE t = m_ownedWeaponList[i]->m_weaponType;
									if (isWeaponAccessible(t))
									{
										m_input.weaponInputIndex = i;
										break;
									}
								}
							}
						}
					}
					else
					{
						for (int i = 0; i < m_ownedWeaponList.size(); ++i)
						{
							Weapon::TYPE t = m_ownedWeaponList[i]->m_weaponType;
							if (isWeaponAccessible(t))
							{
								m_input.weaponInputIndex = i;
								break;
							}
						}
					}
				}
			}

			break;
		}

		case sf::Event::KeyReleased:
		{
			sf::Keyboard::Key key = event.key.code;
			switch (key)
			{
			case sf::Keyboard::A:
				if (m_input.x < 0) m_input.x = 0;
				break;
			case sf::Keyboard::D:
				if (m_input.x > 0) m_input.x = 0;
				break;
			case sf::Keyboard::Space:
				m_input.isJump = false;
				break;
			default:
				break;
			}

			break;
		}

		case sf::Event::MouseWheelScrolled:
		{
			if (!m_ownedWeaponList.empty())
			{
				int& index = m_input.weaponInputIndex;
				int weaponCount = m_ownedWeaponList.size();
				int direction = (event.mouseWheelScroll.delta > 0) ? 1 : -1;

				for (int i = 1; i <= weaponCount; ++i) 
				{
					int nextIndex = (index + direction * i + weaponCount) % weaponCount;

					Weapon::TYPE type = m_ownedWeaponList[nextIndex]->m_weaponType;
					if (isWeaponAccessible(type))
					{
						index = nextIndex;
						break;
					}
				}
			}
			break;
		}

		default:
			break;
		}
	}

	void Player::setPlayerByColliderPos()
	{
	}

	void Player::setPosition(const float x, const float y)
	{
		m_sprite.setPosition(x, y);
	}

	void Player::updateMovement()
	{
		m_movementType = MOVEMENTTYPE_UNKNOWN;
		m_isMoving = false;
		bool changeX = false;
		float xVelocity = 0.0f;
		bool changeY = false;
		float yVelocity = 0.0f;

		if (m_input.x != 0)
		{
			m_isMoving = true;
			changeX = true;
			xVelocity = m_movementSpeed * m_input.x;
		}
		
		if (m_input.isJump && isGrounded())
		{
			m_isMoving = true;
			changeY = true;
			yVelocity = m_jumpImpulse;
		}


		m_movementType = isGrounded() ? GROUND : UNGROUND;

		DBOUT("[PLAYER] BEFORE" << " Velocity " << " X: " << m_collider->m_body->GetLinearVelocity().x << ", Y: " << m_collider->m_body->GetLinearVelocity().y);

		m_collider->applyMovement(changeX, xVelocity, changeY, yVelocity);

		auto playerPosition = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);
		m_sprite.setPosition(playerPosition);

		DBOUT("[PLAYER] AFTER" << " Velocity " << " X: " << m_collider->m_body->GetLinearVelocity().x << ", Y: " << m_collider->m_body->GetLinearVelocity().y);
	}

	void Player::updateRotation()
	{
		m_sprite.rotate(m_rotation);
	}

	void Player::updateJump()
	{
	}

	void Player::updateRunningJump()
	{
	}


	void Player::setIsOnGround(bool isGround)
	{
		// m_isGround = isGround;
	}

	void Player::updateInput()
	{
	}

	Player::~Player() 
	{
	}

#ifdef IS_RATCHET_DEBUG
	void Player::printSpriteColliderPositionPlayer()
	{
		//m_collider->printSpriteColliderPosition(m_sprite, DYNAMIC);
	}
#endif
}