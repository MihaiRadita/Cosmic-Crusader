#include "stdafx.h"
#include "Creature.h"

namespace ratchet
{

	Creature::Creature(const CreatureConfig& config) : GameObject(config)
	{
		//Character Features
		m_movementSpeed = config.m_movingSpeed;
		m_fallingSpeed = config.m_fallingSpeed;
		m_jumpImpulse = config.m_jumpImpulse;

		m_characterAnimator = nullptr;

		m_weaponConfigList = config.m_weaponConfigList;
		m_usableWeaponTypeList = config.m_usableWeaponTypeList;


		creatureFallingTexturePath = config.fallingSpriteTexturePath;

		m_currentWeaponType = config.m_currentWeaponType;
		m_currentCharacterAngle = config.m_currentAngle;
		m_currentCharacterState = config.m_currentState;

		m_isFalling = false;

		if (m_creatureFallingTexture.loadFromFile(creatureFallingTexturePath) == false)
		{
#ifdef IS_RATCHET_DEBUG
			//std::cout << "ERROR::PLAYER COULD NOT LOAD THE TEXTURE SHEET" << std::endl;
#endif
		}

		m_spritePath = config.spriteTexturePath;

		m_sprite.setTexture(m_spriteTexture);

		if (m_sprite.getTexture())
		{
			std::cout << "Precior SUCCESS" << std::endl;
		}

		if (m_sprite.getTexture() != nullptr)
		{
			std::cout << "Character Success" << std::endl;
		}
		else
		{
			std::cout << "Character Failed" << std::endl;
		}

		for (const auto& weponType : m_usableWeaponTypeList)
		{
			Weapon::TYPE type = weponType.first;

			m_usableWeaponTypes.push_back(type);
		}


		//m_usableWeaponTypeList = config.m_usableWeaponTypeList;

		if (m_faction == Faction::PLAYER)
		{
			m_characterAnimationState = IDLE;
			m_characterAnimator = new Animator();
			m_animationList.emplace(ANIMATION_STATE::IDLE, new AnimationIdle(m_spritePath, m_usableWeaponTypes));
			m_animationList.emplace(ANIMATION_STATE::JUMP, new AnimationJump(m_spritePath, m_usableWeaponTypes));
			m_animationList.emplace(ANIMATION_STATE::MOVING, new AnimationRun(m_spritePath, m_usableWeaponTypes));
			m_animationList.emplace(ANIMATION_STATE::JUMP_RUNNING, new AnimationJumpRun(m_spritePath, m_usableWeaponTypes));

			m_characterAnimSwitch = -1;

		}
	}

	Creature::~Creature()
	{
		for (auto& pair : m_animationList)
		{
			delete pair.second;
			pair.second = nullptr;
		}

		delete m_characterAnimator;
		m_characterAnimator = nullptr;
	}

	void Creature::update()
	{
		updateInput();
		m_isGround = m_collider->performGroundRayCast(m_sprite);
		updateMovement();
		updateJump();
		updateAnimations();
		updatePhysics();
	}

	void Creature::updateInput()
	{

	}
	void Creature::updateMovement()
	{
		auto position = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);
		m_sprite.setPosition(position);

		// Sync sprite rotation with collider
		m_rotation = m_collider->getBody()->GetAngle() * (180.f / M_PI);
		m_sprite.setRotation(m_rotation);
	}
	void Creature::updateRotation()
	{
	}
	void Creature::updatePhysics()
	{
	}
	void Creature::updateAnimations()
	{
		if (m_faction == Faction::PLAYER)
		{
			if (m_input.x < 0)
			{
				m_isMoving = true;
				if (m_movementType == GROUND)
				{
					if (isGrounded())
					{
						m_isFalling = false;
						if (m_isMoving)
						{
							if (m_characterAnimationState != MOVING)
							{
								m_characterAnimationState = MOVING;
								switchAnimation();
							}
						}
					}
				}
				invertCharacterMovingSpriteScale(-1);
			}
			else if (m_input.x > 0)
			{
				m_isMoving = true;
				if (m_movementType == GROUND)
				{
					if (isGrounded())
					{
						m_isFalling = false;

						if (m_isMoving)
						{
							if (m_characterAnimationState != MOVING)
							{
								m_characterAnimationState = MOVING;
								switchAnimation();
							}
							
						}
					}
				}
				invertCharacterMovingSpriteScale(1);
			}
			
			if (!isGrounded())
			{
				if (m_characterAnimationState != JUMP && m_characterAnimationState != JUMP_RUNNING)
				{
					m_isFalling = true;
				}
			}

			if (m_input.isJump && isGrounded())
			{
				if (m_characterAnimationState != MOVING)
				{
					if (m_characterAnimationState != JUMP)
					{
						m_characterAnimationState = JUMP;
						m_isFalling = false;
						switchAnimation();
					}
				}
			}
			if (m_input.isJump && isGrounded() && m_isMoving == true)
			{
				if (m_characterAnimationState == MOVING)
				{
					if (m_characterAnimationState != JUMP_RUNNING)
					{
						m_characterAnimationState = JUMP_RUNNING;
						m_isFalling = false;
						switchAnimation();
					}
				}
			}

			if (isNoControlActive() && isGrounded() && m_isMoving == false)
			{
#ifdef IS_RATCHET_DEBUG
				std::cout << "Idle" << std::endl;
				std::cout << m_characterAnimationState << std::endl;
#endif			
				m_isMoving = false;
				m_characterAnimationState = ANIMATION_STATE::IDLE;
				m_isFalling = false;
				switchAnimation();;
			}

		}
		if (!m_isFalling)
		{
			m_characterAnimator->play(m_characterAnimator->getAbstractAnimation(), m_sprite,m_currentWeaponType, m_currentCharacterAngle,m_currentCharacterState);
		}
		else
		{
			m_sprite.setTexture(m_creatureFallingTexture);
		}

			// Sync sprite position with collider
			auto position = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);

			// Sync sprite rotation with collider
			m_rotation = m_collider->getBody()->GetAngle() * (180.f / M_PI);
			m_sprite.setRotation(m_rotation);

	}


#ifdef IS_RATCHET_DEBUG
		//sf::Vector2f playerSpritePosition;
		//playerSpritePosition = m_sprite.getPosition();
		//std::cout << m_sprite.getPosition().x << " , " << m_sprite.getPosition().y;
#endif
	
	void Creature::updateJump()
	{
	}
	void Creature::updateRunningJump()
	{
	}
	void Creature::invertCharacterMovingSpriteScale(int direction)
	{
		m_sprite.setScale(m_scale.x * (float)direction, m_scale.y);
		if (direction < 0)
		{
			m_sprite.setOrigin(getBounds().width / m_scale.x, 0.f);
		}
		else
		{
			m_sprite.setOrigin(0.f, 0.f);
		}
	}
	bool Creature::isNoControlActive()
	{
		if (m_input.x != 0 || m_input.y != 0 || m_input.isJump == true)
		{
			return false;
		}
		return true;
	}
	
	void Creature::switchAnimation()
	{
		if (m_characterAnimationState != m_characterAnimSwitch) {


			m_characterAnimator->resetAnimationTimer(m_characterAnimator->getAbstractAnimation());
			m_characterAnimator->resetAnimIndex(m_characterAnimator->getAbstractAnimation());
			m_characterAnimator->setAnimation(m_animationList[m_characterAnimationState]);
			m_characterAnimator->resetAnimationTimer(m_characterAnimator->getAbstractAnimation());
			m_characterAnimator->resetAnimIndex(m_characterAnimator->getAbstractAnimation());


			// salveaza stare curenta in stare anterioara	
			m_characterAnimSwitch = m_characterAnimationState;
		}
	}

	void Creature::addWeapon(Weapon::TYPE weaponType, std::optional<WeaponConfig> config)
	{
		if (weaponType != Weapon::TYPE::None)
		{
			auto newWeapon = new Weapon(*WeaponManager::instance()->getWeapon(weaponType));
			if (config.has_value())
			{
				newWeapon->m_currentAmmo = config->m_currentAmmo;
			}

			m_ownedWeaponList.push_back(newWeapon);
		}
	}
	void Creature::setWeapon(int weaponIndex)
	{
		if (0 <= weaponIndex && weaponIndex < m_ownedWeaponList.size())
		{
			m_equippedWeaponIndex = weaponIndex;
			m_characterAnimator->setWeapon(m_ownedWeaponList[m_equippedWeaponIndex]->m_weaponType);
		}
		else
		{
			m_equippedWeaponIndex = -1;
			m_characterAnimator->setWeapon(Weapon::TYPE::None);
		}
	}
}

