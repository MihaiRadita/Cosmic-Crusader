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
		m_bodShoulderOffset = config.m_bodShoulderOffset;

		//Angles
		m_baseAngle = config.m_AngleBase;
		m_HalfBaseAngle = m_baseAngle / 2.0f;
		TRACE_CHANNEL(TR_GAMEOBJECT_INIT, m_baseAngle / 2.0f << " ");

		m_DEG_TO_RAD = M_PI / 180.0f;
		m_tangentHalfBase = tan((m_baseAngle / 2.0f) * m_DEG_TO_RAD);
		m_tangentx3HalfBase = tan((3.0f * m_baseAngle / 2.0f) * m_DEG_TO_RAD);

		m_currentEcquipedWeaponIndex = config.m_currentlyEquippedWeaponIndex;
		m_currentWeaponType = config.m_currentWeaponType;

		m_characterAnimator = nullptr;

		m_initialWeaponConfigList = config.m_initialWeaponConfigList;
		m_weaponTypeList = config.m_weaponTypeList;
		m_usableWeaponTypeList = config.m_usableWeaponTypeList;
		m_characterAngles = config.m_characterAngles;


		creatureFallingTexturePath = config.fallingSpriteTexturePath;

		m_currentWeaponType = config.m_currentWeaponType;
		m_currentCharacterAngle = config.m_currentAngle;
		m_currentCharacterState = config.m_currentState;

		m_isFallingWithoutJumping = false;

		if (m_creatureFallingTexture.loadFromFile(creatureFallingTexturePath) == false)
		{
#ifdef IS_RATCHET_DEBUG
			TRACE_CHANNEL(TR_GAMEOBJECT_INIT, "ERROR::PLAYER COULD NOT LOAD THE TEXTURE SHEET");
#endif
		}

		m_spritePath = config.spriteTexturePath;

		m_sprite.setTexture(m_spriteTexture);

		if (m_sprite.getTexture())
		{
			TRACE_CHANNEL(TR_GAMEOBJECT_INIT, "Precior SUCCESS");
		}

		if (m_sprite.getTexture() != nullptr)
		{
			TRACE_CHANNEL(TR_GAMEOBJECT_INIT, "Character Success");
		}
		else
		{
			TRACE_CHANNEL(TR_GAMEOBJECT_INIT, "Character Failed");
		}

		for (auto config : m_initialWeaponConfigList)
		{

			addWeapon(config.first, config.second);
		}


		//m_usableWeaponTypeList = config.m_usableWeaponTypeList;

		if (m_faction == Faction::PLAYER)
		{
			m_characterAnimationState = IDLE;
			m_characterAnimator = new Animator();
			m_animationList.emplace(ANIMATION_STATE::IDLE, new AnimationIdle(m_spritePath, m_weaponTypeList));
			m_animationList.emplace(ANIMATION_STATE::JUMP, new AnimationJump(m_spritePath, m_weaponTypeList));
			m_animationList.emplace(ANIMATION_STATE::MOVING, new AnimationRun(m_spritePath, m_weaponTypeList));
			m_animationList.emplace(ANIMATION_STATE::JUMP_RUNNING, new AnimationJumpRun(m_spritePath, m_weaponTypeList));
			m_animationList.emplace(ANIMATION_STATE::FALL, new AnimationFall(m_spritePath, m_weaponTypeList));

			m_characterAnimSwitch = -1;

		}
		setWeapon(m_currentEcquipedWeaponIndex);


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

		for (auto& weapon : m_ownedWeaponList)
		{
			delete weapon;
		}
	}

	void Creature::update()
	{
		updateInput();
		if (m_collider && !m_collider->m_skipRaycastThisFrame)
		{
			m_isGround = m_collider->performGroundRayCast(m_sprite);
		}
		else
		{
			m_isGround = false;
			m_collider->m_skipRaycastThisFrame = false;
		}
		//m_isGround = m_collider->performGroundRayCast(m_sprite);

		updateWeaponSelection();
		updateMovement();
		updateJump();
		computeAimAngleState();
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
				m_animDirectionReverse = true;
				if (m_movementType == GROUND)
				{
					if (isGrounded())
					{
						m_isFallingWithoutJumping = false;
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
						m_isFallingWithoutJumping = false;

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
				if (m_currentWeaponType != Weapon::TYPE::None)
				{
					m_animDirectionReverse = true;
					
				}
				else
				{
					invertCharacterMovingSpriteScale(1);
				}

				if (m_animDirectionReverse == true)
				{

				}
			}

			if (!isGrounded())
			{
				if (m_characterAnimationState != JUMP && m_characterAnimationState != JUMP_RUNNING)
				{
					if (m_characterAnimationState != FALL)
					{
						m_characterAnimationState = FALL;
						switchAnimation();
					}
				}
			}

			if (m_input.isJump && isGrounded())
			{
				if (m_characterAnimationState != MOVING)
				{
					if (m_characterAnimationState != JUMP)
					{
						m_characterAnimationState = JUMP;
						m_isFallingWithoutJumping = false;
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
						m_isFallingWithoutJumping = false;
						switchAnimation();
					}
				}
			}

			if (isNoControlActive() && isGrounded() && m_isMoving == false)
			{
#ifdef IS_RATCHET_DEBUG
				TRACE_CHANNEL(TR_ANIMATION, "Idle");
				TRACE_CHANNEL(TR_ANIMATION, m_characterAnimationState);
#endif			
				m_isMoving = false;
				m_characterAnimationState = ANIMATION_STATE::IDLE;
				m_isFallingWithoutJumping = false;
				switchAnimation();
			}

		}


		m_characterAnimator->play(m_characterAnimator->getAbstractAnimation(), m_sprite, m_currentWeaponType, m_currentCharacterAngle, m_currentCharacterState);



		// Sync sprite position with collider
		auto position = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);

		// Sync sprite rotation with collider
		m_rotation = m_collider->getBody()->GetAngle() * (180.f / M_PI);
		m_sprite.setRotation(m_rotation);

	}

	void Creature::updateJump()
	{
	}
	void Creature::updateRunningJump()
	{
	}

	void Creature::updateWeaponSelection()
	{
		if (m_currentEcquipedWeaponIndex != m_input.weaponInputIndex)
		{
			m_currentEcquipedWeaponIndex = m_input.weaponInputIndex;
			setWeapon(m_currentEcquipedWeaponIndex);
		}
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

	int Creature::getWeaponListSize()
	{
		return m_ownedWeaponList.size();
	}

	void Creature::addWeapon(Weapon::TYPE& weaponType, std::optional<WeaponConfig>& config)
	{

		auto newWeapon = new Weapon(*WeaponManager::instance()->getWeapon(weaponType));
		if (config.has_value())
		{
			newWeapon->m_currentAmmo = config->m_MaxAmmo;
		}

		newWeapon->m_weaponType = weaponType;



		m_ownedWeaponList.push_back(newWeapon);

		if (m_ownedWeaponList.empty()) {
			std::cerr << "Error: m_ownedWeaponList is empty!\n";
			return;
		}


		if (!m_ownedWeaponList[m_currentEcquipedWeaponIndex]) {
			TRACE_CHANNEL(TR_WEAPON, "Error: Weapon at index " << m_equippedWeaponIndex << " is nullptr!");
			return;
		}
	}
	void Creature::setWeapon(int& weaponIndex)
	{
		if (0 <= weaponIndex && weaponIndex < m_ownedWeaponList.size())
		{
			
			Weapon* weapon = m_ownedWeaponList[weaponIndex];

			if (isWeaponAccessible(weapon->m_weaponType))
			{
				m_currentWeaponType = weapon->m_weaponType;
				m_characterAnimator->setWeapon(m_currentWeaponType);
			}


		}
		else
		{
			weaponIndex = 0;
			m_characterAnimator->setWeapon(Weapon::TYPE::None);
		}
	}
	void Creature::setWeaponAccessible(Weapon::TYPE& weaponType, bool isAccessible)
	{
		for (auto& weapon : m_usableWeaponTypeList)
		{
			if (weapon.first == weaponType)
			{
				weapon.second = isAccessible;
				break;
			}
		}
	}
	void Creature::setWeaponIndex(int index)
	{
		m_input.weaponInputIndex = index;
		m_currentEcquipedWeaponIndex = m_input.weaponInputIndex;
		
	}
	bool Creature::isWeaponMatchCharacter(Weapon::TYPE& weaponType)
	{
		for (auto& weapon : m_weaponTypeList)
		{
			if(weapon == weaponType)
			{
				return true;
			}
		}
		return false;
	}
	bool Creature::isWeaponAccessible(Weapon::TYPE& weaponType)
	{
		for (auto& weapon : m_usableWeaponTypeList)
		{
			if (weapon.first == weaponType)
			{
				if (weapon.second)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		return false;
	}
	void Creature::computeAimAngleState()
	{
	}
}

