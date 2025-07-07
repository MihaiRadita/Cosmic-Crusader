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
		TRACE_CHANNEL("GAMEOBJECT_INIT", m_baseAngle / 2.0f, " ");

		m_DEG_TO_RAD = M_PI / 180.0f;
		m_tangentHalfBase = tan((m_baseAngle / 2.0f) * m_DEG_TO_RAD);
		m_tangentx3HalfBase = tan((3.0f * m_baseAngle / 2.0f) * m_DEG_TO_RAD);

		m_currentEquippedWeaponIndex = config.m_currentlyEquippedWeaponIndex;
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
			TRACE_CHANNEL("GAMEOBJECT_INIT", "ERROR::PLAYER COULD NOT LOAD THE TEXTURE SHEET");
#endif
		}

		m_spritePath = config.spriteTexturePath;

		m_sprite.setTexture(m_spriteTexture);

		if (m_sprite.getTexture())
		{
			TRACE_CHANNEL("GAMEOBJECT_INIT", "Precior SUCCESS");
		}

		if (m_sprite.getTexture() != nullptr)
		{
			TRACE_CHANNEL("GAMEOBJECT_INIT", "Character Success");
		}
		else
		{
			TRACE_CHANNEL("GAMEOBJECT_INIT", "Character Failed");
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
		setWeapon(m_currentEquippedWeaponIndex);

		m_characterShootingPosition = sf::CircleShape(0.05);
		m_characterShootingPosition.setFillColor(sf::Color::Yellow);
		m_characterShootingPosition.setPosition(getPosition().x, getPosition().y);

		m_shootingPointDynamic = sf::CircleShape(0.05);
		m_shootingPointDynamic.setFillColor(sf::Color::Blue);
		m_shootingPointDynamic.setPosition(getPosition().x, getPosition().y);

		m_isRightNoWeapon = true;
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

		auto mousePosition = sf::Mouse::getPosition(*WindowManager::Get());
		auto mouseWorldPosition = WindowManager::Get()->mapPixelToCoords(mousePosition);
		
		if (currentMousePositiion != mouseWorldPosition)
		{
			currentMousePositiion = mouseWorldPosition;

			TRACE_CHANNEL("MOUSE_POSITION", "CURRENT MOUSE POSITION = ", currentMousePositiion.x, " , ", currentMousePositiion.y);
		}

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
		computeShootingPoint();
		updateAnimations();
		updateShooting();
		updatePhysics();

		m_characterShootingPosition.setPosition(getPosition().x, getPosition().y);
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
			if (m_input.x != 0.0f)
			{
				const auto isMovingRight = m_input.x > 0.0f ? true : false;
				m_isMoving = true;
				if (m_movementType == MovementType::GROUND)
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
					if (isGrounded())
					{
						if (isMovingRight != m_facingRight)
						{
							if (!m_isAnimationInverted)
							{
								m_characterAnimator->invertAnimation(m_characterAnimator->getAbstractAnimation(), m_currentWeaponType);
								m_isAnimationInverted = true;
							}

						}
						else
						{
							if (m_isAnimationInverted)
							{
								m_characterAnimator->invertAnimation(m_characterAnimator->getAbstractAnimation(), m_currentWeaponType);
								m_isAnimationInverted = false;
							}
						}
					}
				}
				else
				{
					invertCharacterMovingSpriteScale(isMovingRight ? 1 : -1);
					m_isRightNoWeapon = isMovingRight;
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
						switchAnimation();
					}
				}
			}

			if (isNoControlActive() && isGrounded() && m_isMoving == false)
			{
#ifdef IS_RATCHET_DEBUG
			TRACE_CHANNEL("ANIMATION", "Idle");
			TRACE_CHANNEL("ANIMATION", m_characterAnimationState);
#endif			
				m_isMoving = false;
				m_characterAnimationState = ANIMATION_STATE::IDLE;
				switchAnimation();
			}

			if (m_currentWeaponType != Weapon::TYPE::None)
			{
				bool isOnRecoil = m_currentCharacterState == WeaponAnimation::STATE::Recoil;
				const auto justPassedRecoilTime = isOnRecoil && m_fireCooldown.getElapsedTime().asSeconds() >= m_recoilTime;

				if (justPassedRecoilTime)
				{
					m_currentCharacterState = WeaponAnimation::STATE::Aim;
					isOnRecoil = false;
				}

				if (m_input.m_isFiring)
				{
					if (isOnRecoil == false)
					{
						const auto firstTimeFiringThisWeapon = m_lastFiredWeaponIndex != m_currentEquippedWeaponIndex;
						const auto isReadyToFire = firstTimeFiringThisWeapon || m_fireCooldown.getElapsedTime().asSeconds() >= m_fireRate;
						if (isReadyToFire)
						{
							m_fireCooldown.restart();
							m_currentCharacterState = WeaponAnimation::STATE::Recoil;
#ifdef IS_RATCHET_DEBUG
							TRACE_CHANNEL("WEAPON_FIRE", "Must Spawn Bullet = true");
#endif	
							m_mustSpawnBullet = true;

							m_lastFiredWeaponIndex = m_currentEquippedWeaponIndex;
						}
					}
				}
			}

			m_characterAnimator->play(m_characterAnimator->getAbstractAnimation(), m_sprite, m_currentWeaponType, m_currentCharacterAngle, m_currentCharacterState);


			// Sync sprite position with collider
			auto position = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);

			// Sync sprite rotation with collider
			m_rotation = m_collider->getBody()->GetAngle() * (180.f / M_PI);
			m_sprite.setRotation(m_rotation);

		}
	}
	void Creature::updateJump()
	{
	}
	void Creature::updateRunningJump()
	{
	}

	void Creature::updateWeaponSelection()
	{
		if (m_currentEquippedWeaponIndex != m_input.weaponInputIndex)
		{
			m_currentEquippedWeaponIndex = m_input.weaponInputIndex;
			setWeapon(m_currentEquippedWeaponIndex);
		}
	}

	void Creature::updateShootPoint()
	{
		
	}

	void Creature::updateShooting()
	{
		if (m_mustSpawnBullet)
		{
			m_ownedWeaponList[m_currentEquippedWeaponIndex]->Fire(m_currentFirePoint, 0.0f, 0.0f);
#ifdef IS_RATCHET_DEBUG
			TRACE_CHANNEL("WEAPON_FIRE", "Must Spawn Bullet = false");
#endif	
			m_mustSpawnBullet = false;

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

		auto shootingPointXOffset = 0.0f;
		auto shootingPointYOffset = 0.0f;


		if (config.has_value())
		{
			newWeapon->m_currentAmmo = config->m_MaxAmmo;
			shootingPointXOffset = config->m_weaponShootPointOffsetX;
			shootingPointYOffset = config->m_weaponShootPointOffsetY;
			newWeapon->m_WeaponID = config->m_configLayer;
		}

		newWeapon->m_weaponType = weaponType;

		//newWeapon->m_curreW

	

		m_ownedWeaponList.push_back(newWeapon);

		if (m_ownedWeaponList.empty()) {
			TRACE_CHANNEL("WEAPON", "Error: m_ownedWeaponList is empty!\n");
			return;
		}


		if (!m_ownedWeaponList[m_currentEquippedWeaponIndex]) {
			TRACE_CHANNEL("WEAPON", "Error: Weapon at index ", m_equippedWeaponIndex, " is nullptr!");
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
		m_currentEquippedWeaponIndex = m_input.weaponInputIndex;
		
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
	void Creature::computeShootingPoint()
	{
		if (m_currentWeaponType != Weapon::TYPE::None)
		{

			sf::Vector2f characterPointPositiion;
			float dir = m_facingRight ? 1.f : -1.f;


			if (dir < 0.f)
			{
				characterPointPositiion = sf::Vector2f(getPosition().x, getPosition().y - m_weaponsStartShootingPoint[m_currentWeaponType].y);
			}
			else
			{
				characterPointPositiion = sf::Vector2f(getPosition().x - m_weaponsStartShootingPoint[m_currentWeaponType].x, 
										  getPosition().y - m_weaponsStartShootingPoint[m_currentWeaponType].y);
			}
	

			sf::Vector2f shootingPoint;
	

			switch (m_currentCharacterAngle) {
			case WeaponAnimation::ANGLE::Angle0:
				shootingPoint = {  characterPointPositiion.x + dir * m_shootingPointsOffsets[m_currentWeaponType][m_currentCharacterAngle].x, characterPointPositiion.y};
				break;
			case WeaponAnimation::ANGLE::Angle45:
				shootingPoint = { characterPointPositiion.x + dir * m_shootingPointsOffsets[m_currentWeaponType][m_currentCharacterAngle].x, 
								characterPointPositiion.y - m_shootingPointsOffsets[m_currentWeaponType][m_currentCharacterAngle].y};
				break;

			case WeaponAnimation::ANGLE::Angle90:


				shootingPoint = { characterPointPositiion.x, characterPointPositiion.y - m_shootingPointsOffsets[m_currentWeaponType][m_currentCharacterAngle].y};
				break;
			case WeaponAnimation::ANGLE::AngleMinus45:

				shootingPoint = { characterPointPositiion.x +  dir* m_shootingPointsOffsets[m_currentWeaponType][m_currentCharacterAngle].x, 
								characterPointPositiion.y + m_shootingPointsOffsets[m_currentWeaponType][m_currentCharacterAngle].y};
				break;
			}

			if (m_currentFirePoint != shootingPoint) {
				m_currentFirePoint = shootingPoint;
			}
		}
		else
		{
			sf::Vector2f characterPointPositiion;
			float dir = m_isRightNoWeapon ? 1.f : -1.f;
			if (dir < 0.f)
			{
				characterPointPositiion = sf::Vector2f(getPosition().x, getPosition().y);
			}
			else
			{
				characterPointPositiion = sf::Vector2f(getPosition().x - m_weaponsStartShootingPoint[m_currentWeaponType].x, getPosition().y);
			}

			if (m_currentFirePoint != characterPointPositiion) {
				m_currentFirePoint = characterPointPositiion;
			}
		}
		m_shootingPointDynamic.setPosition(m_currentFirePoint);
	}
}

