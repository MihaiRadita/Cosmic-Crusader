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

		case sf::Event::MouseButtonPressed:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (!m_input.m_isFiring)
					m_input.m_isFiring = true;
			}
			break;
		}

		case sf::Event::MouseButtonReleased:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (m_input.m_isFiring)
					m_input.m_isFiring = false;
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

	void Player::computeAimAngleState()
	{
		if (m_currentWeaponType != Weapon::TYPE::None)
		{
			WeaponAnimation::ANGLE weaponAnimationAngle;
			
			m_bodyShoulderPosition = getPosition();
			auto mousePosition = sf::Mouse::getPosition(*WindowManager::Get());
			auto mouseWorldPosition = WindowManager::Get()->mapPixelToCoords(mousePosition);


			auto shoulderToMouseVector = mouseWorldPosition - m_bodyShoulderPosition;
			auto facingRight = shoulderToMouseVector.x >= 0;
			// Normalize Begin
			auto shoulderToMouseLength = std::sqrt(std::pow(shoulderToMouseVector.x, 2) + std::pow(shoulderToMouseVector.y, 2));
			auto directionVector = 
				shoulderToMouseLength != 0 ? 
				sf::Vector2f(shoulderToMouseVector.x / shoulderToMouseLength, shoulderToMouseVector.y / shoulderToMouseLength) \
				: (facingRight ? sf::Vector2f(1, 0) : sf::Vector2f(-1, 0));
			// Normalize End
			
			// Calculate Angle Begin
			auto vectorToCalculateAngleAgainst = facingRight ? sf::Vector2f(1, 0) : sf::Vector2f(-1, 0);
			auto dotProduct = directionVector.x * vectorToCalculateAngleAgainst.x + directionVector.y * vectorToCalculateAngleAgainst.y;
			auto determinant = directionVector.x * vectorToCalculateAngleAgainst.y - directionVector.y * vectorToCalculateAngleAgainst.x;
			float angleRad = (facingRight ? 1 : -1) * atan2(determinant, dotProduct);
			float angleDeg = angleRad * (180.f / M_PI); 
				
			TRACE_CHANNEL("MOUSE", "Pos Vect: ", getPosition().x, ", ", getPosition().y);
			TRACE_CHANNEL("MOUSE", "Dir Vect: ", directionVector.x, ", ", directionVector.y);
			TRACE_CHANNEL("MOUSE", "Angle: ", angleDeg);

			const float minus45 = -m_HalfBaseAngle;        // -22.5
			const float minus135 = -m_HalfBaseAngle * 3.f; // -67.5
			const float plus45 = m_HalfBaseAngle;          // 22.5
			const float plus135 = m_HalfBaseAngle * 3.f;   // 67.5

			if (minus135 <= angleDeg && angleDeg <= minus45)
			{
				weaponAnimationAngle = WeaponAnimation::ANGLE::AngleMinus45; // Dreapta sus
			}
			else if (minus45 <= angleDeg && angleDeg <= plus45)
			{
				weaponAnimationAngle = WeaponAnimation::ANGLE::Angle0; // Dreapta
			}
			else if (plus45 <= angleDeg && angleDeg <= plus135)
			{
				weaponAnimationAngle = WeaponAnimation::ANGLE::Angle45; // Dreapta jos
			}
			else if(plus135 <= angleDeg) // Cazul pentru SUS extrem (sub -67.5 sau peste 67.5)
			{
				weaponAnimationAngle = WeaponAnimation::ANGLE::Angle90;
			}
			// Calculate Angle End

			if (std::find(m_characterAngles.begin(), m_characterAngles.end(), weaponAnimationAngle) != m_characterAngles.end())
			{
				m_currentCharacterAngle = weaponAnimationAngle;
			}
			else
			{
				m_currentCharacterAngle = WeaponAnimation::ANGLE::Angle0;
			}

			invertCharacterMovingSpriteScale(facingRight ? 1 : -1);

			m_facingRight = facingRight;
		}
	}

	void Player::updateMovement()
	{
		m_movementType = MovementType::MOVEMENTTYPE_UNKNOWN;
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


		m_movementType = isGrounded() ? MovementType::GROUND : MovementType::AIR;

		TRACE_CHANNEL("PHYSICS", "[PLAYER] BEFORE", " Velocity ", " X: ", m_collider->m_body->GetLinearVelocity().x, ", Y: ", m_collider->m_body->GetLinearVelocity().y);

		m_collider->applyMovement(changeX, xVelocity, changeY, yVelocity);

		auto playerPosition = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);
		setPosition(playerPosition);

		TRACE_CHANNEL("PHYSICS", "[PLAYER] AFTER", " Velocity ", " X: ", m_collider->m_body->GetLinearVelocity().x, ", Y: ", m_collider->m_body->GetLinearVelocity().y);
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

	void Player::render(sf::RenderTarget& target)
	{
#ifdef IS_RATCHET_DEBUG
		if (m_debugDraw)
		{
			// DRAW LOOK DIRECTION (between shoulder and mouse)
			{
				if (const auto* window = WindowManager::Get())
				{
					sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
					sf::Vector2f mouseWorldPosition = WindowManager::Get()->mapPixelToCoords(mousePosition);

					auto mouseCircleShape = sf::CircleShape(0.05f);
					mouseCircleShape.setFillColor(sf::Color::Transparent);
					mouseCircleShape.setOutlineColor(sf::Color::Yellow);
					mouseCircleShape.setOutlineThickness(0.03f);
					const auto position = mouseWorldPosition;
					mouseCircleShape.setPosition(position.x - mouseCircleShape.getRadius(), position.y - mouseCircleShape.getRadius());
					target.draw(mouseCircleShape);
				}
			}
		}
#endif


		GameObject::render(target);
		target.draw(m_characterShootingPosition);
		target.draw(m_shootingPointDynamic);
		target.draw(m_shooitngPointCenter);
	}

#ifdef IS_RATCHET_DEBUG
	void Player::printSpriteColliderPositionPlayer()
	{
		m_collider->printSpriteColliderPosition(m_sprite, DYNAMIC);
	}
#endif

}