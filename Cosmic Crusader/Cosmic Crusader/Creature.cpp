#include "stdafx.h"
#include "Creature.h"

//#include "game/Player.h"

#include "EnumMask.h"

#include "SceneManager.h"


namespace ratchet
{

	Creature::Creature(const CreatureConfig& config) : GameObject(config)
	{
		

		//Character Features
		m_movementSpeed = config.m_movingSpeed;
		m_fallingSpeed = config.m_fallingSpeed;
		m_jumpImpulse = config.m_jumpImpulse;
		m_bodShoulderOffset = config.m_bodShoulderOffset;

		m_fireRate = config.m_fireRate;
		m_recoilTime = config.m_recoilTime;

		m_fireCooldown = Timer();

		//Angles
		m_baseAngle = config.m_AngleBase;
		m_HalfBaseAngle = m_baseAngle / 2.0f;
		TRACE_CHANNEL("GAMEOBJECT_INIT", m_baseAngle / 2.0f, " ");

		m_targetMaxDistanceDetectionX = config.m_targetMaxDistanceDetectionX;
		m_targetMaxDistanceDetectionY = config.m_targetMaxDistanceDetectionY;
		m_targetMaxDistanceLoseX = config.m_targetMaxDistanceLoseX;
		m_targetMaxDistanceLoseY = config.m_targetMaxDistanceLoseY;

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

			if (config.second.has_value())
			{
				m_weaponsStartShootingPoint[config.first] = config.second->m_characterStartPointShootingOffset;

				std::map<WeaponAnimation::ANGLE, sf::Vector2f> angleOffsets;

				for (auto& angle : m_characterAngles)
				{
					if (angle == WeaponAnimation::ANGLE::Angle0)
					{
						angleOffsets[angle] = config.second->m_shootingOffsetAngle0;
					}
					else if (angle == WeaponAnimation::ANGLE::Angle45)
					{
						angleOffsets[angle] = config.second->m_shootingOffsetAngle45;
					}
					else if (angle == WeaponAnimation::ANGLE::Angle90)
					{
						angleOffsets[angle] = config.second->m_shootingOffsetAngle90;
					}
					else if (angle == WeaponAnimation::ANGLE::AngleMinus45)
					{
						angleOffsets[angle] = config.second->m_shootingOffsetAngleMinus45;
					}
				}

				for (const auto& [angle, offset] : angleOffsets)
				{
					m_shootingPointsOffsets[config.first][angle] = offset;
				}

				addWeapon(config.first, config.second);
			}
			else
			{
				addWeapon(config.first, config.second);
			}

		}

		m_animationStates = config.m_animationStates;
		m_currentAnimationState = config.m_currentAnimationState;
		m_characterAnimator = new Animator();

		for (auto& animationState : m_animationStates)
		{
			switch (animationState)
			{
			case ANIMATION_STATE::IDLE:
				m_animationList.emplace(ANIMATION_STATE::IDLE, new AnimationIdle(m_spritePath, m_weaponTypeList));
				break;
			case ANIMATION_STATE::MOVING:
				m_animationList.emplace(ANIMATION_STATE::MOVING, new AnimationRun(m_spritePath, m_weaponTypeList));
				break;
			case ANIMATION_STATE::JUMP:
				m_animationList.emplace(ANIMATION_STATE::JUMP, new AnimationJump(m_spritePath, m_weaponTypeList));
				break;
			case ANIMATION_STATE::JUMP_RUNNING:
				m_animationList.emplace(ANIMATION_STATE::JUMP_RUNNING, new AnimationJumpRun(m_spritePath, m_weaponTypeList));
				break;
			case ANIMATION_STATE::FALL:
				m_animationList.emplace(ANIMATION_STATE::FALL, new AnimationFall(m_spritePath, m_weaponTypeList));
				break;
			}
		}

		m_characterAnimSwitch = -1;

		setWeapon(m_currentEquippedWeaponIndex);

		m_characterShootingPosition = sf::CircleShape(0.05);
		m_characterShootingPosition.setFillColor(sf::Color::Yellow);
		m_characterShootingPosition.setPosition(getPosition().x, getPosition().y);

		m_shootingPointDynamic = sf::CircleShape(0.05);
		m_shootingPointDynamic.setFillColor(sf::Color::Blue);
		m_shootingPointDynamic.setOrigin(m_shootingPointDynamic.getRadius(), m_shootingPointDynamic.getRadius());
		m_shootingPointDynamic.setPosition(getPosition().x, getPosition().y);

		m_shooitngPointCenter = sf::CircleShape(0.02f);
		m_shooitngPointCenter.setFillColor(sf::Color::Red);
		m_shooitngPointCenter.setOrigin(m_shooitngPointCenter.getRadius(), m_shooitngPointCenter.getRadius());
		m_shooitngPointCenter.setPosition(m_shootingPointDynamic.getPosition().x, m_shootingPointDynamic.getPosition().y);

		m_isRightNoWeapon = true;

		PostCosntructFixup();
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
		if (!m_activeGameObject) return;

		updateWeaponSelection();
		updateMovement();
		updateJump();
		computeAimAngleState();
		computeAimBulletRotation();
		computeShootingPoint();
		updateAnimations();
		updateShooting();
		updatePhysics();
		
	}

	void Creature::updateMovement()
	{
		
	}
	void Creature::updateRotation()
	{
	}
	void Creature::updatePhysics()
	{

	}
	void Creature::updateAnimations()
	{
		if (m_faction == Faction::TEAM_0)
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
							if (m_currentAnimationState != MOVING)
							{
								m_currentAnimationState = MOVING;
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
				if (m_currentAnimationState != JUMP && m_currentAnimationState != JUMP_RUNNING)
				{
					if (m_currentAnimationState != FALL)
					{
						m_currentAnimationState = FALL;
						switchAnimation();
					}
				}
			}

			if (m_input.isJump && isGrounded())
			{
				if (m_currentAnimationState != MOVING)
				{
					if (m_currentAnimationState != JUMP)
					{
						m_currentAnimationState = JUMP;
						m_isFallingWithoutJumping = false;
						switchAnimation();
					}
				}
			}
			if (m_input.isJump && isGrounded() && m_isMoving == true)
			{
				if (m_currentAnimationState == MOVING)
				{
					if (m_currentAnimationState != JUMP_RUNNING)
					{
						m_currentAnimationState = JUMP_RUNNING;
						switchAnimation();
					}
				}
			}

			if (isNoControlActive() && isGrounded() && m_isMoving == false)
			{
#ifdef IS_RATCHET_DEBUG
			TRACE_CHANNEL("ANIMATION", "Idle");
			TRACE_CHANNEL("ANIMATION", m_currentAnimationState);
#endif			
				m_isMoving = false;
				m_currentAnimationState = ANIMATION_STATE::IDLE;
				switchAnimation();
			}

			if (m_currentWeaponType != Weapon::TYPE::None)
			{
				bool isOnRecoil = m_currentCharacterState == WeaponAnimation::STATE::Recoil;
				const auto justPassedRecoilTime = isOnRecoil && m_fireCooldown.m_clock.getElapsedTime().asSeconds() >= m_recoilTime;

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
						const auto isReadyToFire = firstTimeFiringThisWeapon || m_fireCooldown.m_clock.getElapsedTime().asSeconds() >= m_fireRate;
						if (isReadyToFire)
						{
							m_fireCooldown.m_clock.restart();
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
		else if (m_faction == Faction::TEAM_1)
		{

			if (m_input.x != 0.0f)
			{
				m_isMoving = true;
				if (m_movementType == MovementType::GROUND)
				{
					if (isGrounded())
					{
						m_isFallingWithoutJumping = false;
						if (m_isMoving)
						{
							if (m_currentAnimationState != MOVING)
							{
								m_currentAnimationState = MOVING;
								switchAnimation();
							}
						}
					}
				}
			}

			if (!isGrounded())
			{
				if (m_currentAnimationState != JUMP && m_currentAnimationState != JUMP_RUNNING)
				{
					if (m_currentAnimationState != FALL)
					{
						m_currentAnimationState = FALL;
						switchAnimation();
					}
				}
			}

			if (m_input.isJump && isGrounded() && m_isMoving == true)
			{
				if (m_currentAnimationState == MOVING)
				{
					if (m_currentAnimationState != JUMP)
					{
						m_currentAnimationState = JUMP;
						switchAnimation();
					}
				}
			}

			if (isNoControlActive() && isGrounded() && m_isMoving == false)
			{
#ifdef IS_RATCHET_DEBUG
				TRACE_CHANNEL("ANIMATION", "Idle");
				TRACE_CHANNEL("ANIMATION", m_currentAnimationState);
#endif			
				m_isMoving = false;
				m_currentAnimationState = ANIMATION_STATE::IDLE;
				switchAnimation();
			}

			if (m_currentWeaponType != Weapon::TYPE::None)
			{
				bool isOnRecoil = m_currentCharacterState == WeaponAnimation::STATE::Recoil;
				const auto justPassedRecoilTime = isOnRecoil && m_fireCooldown.m_clock.getElapsedTime().asSeconds() >= m_recoilTime;

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
						const auto isReadyToFire = firstTimeFiringThisWeapon || m_fireCooldown.m_clock.getElapsedTime().asSeconds() >= m_fireRate;
						if (isReadyToFire)
						{
							m_fireCooldown.m_clock.restart();
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

	void Creature::updateShooting()
	{
		if (m_mustSpawnBullet)
		{
			m_ownedWeaponList[m_currentEquippedWeaponIndex]->Fire(m_currentFirePoint, m_currentFireRoationDegrees, m_currenFireDirectionNorm, m_facingRight);
#ifdef IS_RATCHET_DEBUG
			TRACE_CHANNEL("WEAPON_FIRE", "Must Spawn Bullet = false");
#endif	
			m_mustSpawnBullet = false;

		}
	}

	void Creature::serialise(nlohmann::json& jsonFile)
	{
		 GameObject::serialise(jsonFile);

		 jsonFile["x"] = m_position.x + m_checkPointOffsetX;
		 jsonFile["y"] = m_position.x + m_checkPointOffsetY;

		EnumMask<Weapon::TYPE> saveMask;

		for (auto& weapons : m_ownedWeaponList)
		{
			if (weapons->m_weaponType != Weapon::TYPE::None)
			{
				for (const auto& [weaponType, isUsable] : m_usableWeaponTypeList)
				{
					if (isUsable)
					{
						saveMask.addValue(weaponType);

						for (auto& prop : jsonFile["properties"])
						{
							auto& propName = prop["name"];
							auto& propValue = prop["value"];

							if (propName == "usableWeaponCheckListMask")
							{
								propValue = saveMask.getRawValue();
								break;
							}
						}


						nlohmann::json weponWasPcikedUp;
						if (SceneManager::Get().FindObjectById(weapons->m_WeaponID, weponWasPcikedUp,
							SceneManager::Get().GetLayerNameObjectByID(weapons->m_WeaponID)))
						{
							for (auto& prop : weponWasPcikedUp["properties"])
							{
								auto& propName = prop["name"];
								auto& propValue = prop["value"];

								if (propName == "isWeaponAccesible")
								{
									propValue = !isUsable;
									break;
								}
							}
						}
					}
				}
			}
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

	void Creature::PostCosntructFixup()
	{
		if (m_collider) {
			m_collider->SetOwner(this); // now it's really Creature*
		}
	}

	void Creature::Start()
	{
		PostCosntructFixup();
	}

	void Creature::switchAnimation()
	{
		if (m_currentAnimationState != m_characterAnimSwitch) {


			m_characterAnimator->resetAnimationTimer(m_characterAnimator->getAbstractAnimation());
			m_characterAnimator->resetAnimIndex(m_characterAnimator->getAbstractAnimation());
			m_characterAnimator->setAnimation(m_animationList[m_currentAnimationState]);
			m_characterAnimator->resetAnimationTimer(m_characterAnimator->getAbstractAnimation());
			m_characterAnimator->resetAnimIndex(m_characterAnimator->getAbstractAnimation());


			// salveaza stare curenta in stare anterioara	
			m_characterAnimSwitch = m_currentAnimationState;
		}
	}

	void Creature::detectTarget(GameObject* target)
	{


		sf::Vector2f targetdistancevector = this->getPosition() - target->getPosition();

		if (targetdistancevector.x > 0.0f)
		{
			m_isTagetBehindCharacter = true;
		}
		else if(targetdistancevector.x < 0.0f)
		{
			m_isTagetBehindCharacter = false;
			targetdistancevector.x *= -1.f;
		}

		if (targetdistancevector.y < 0.0f)
		{
			//targetdistancevector.y *= -1.f;
		}

		if (targetdistancevector.x <= m_targetMaxDistanceDetectionX)
		{
			m_isTargetDetected = true;
			
		}
		else if (targetdistancevector.x >= m_targetMaxDistanceLoseX)
		{
			m_isTargetDetected = false;
			
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
			newWeapon->m_WeaponID = config->m_objectID;
			newWeapon->m_bulletID = config->m_bulletID;
			newWeapon->m_bulletPoolIncrementation = config->m_bulletPoolIncrementation;

		}

		newWeapon->m_weaponType = weaponType;

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
	void Creature::computeAimBulletRotation()
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
				characterPointPositiion = sf::Vector2f(getPosition().x +  m_weaponsStartShootingPoint[m_currentWeaponType].x, getPosition().y - m_weaponsStartShootingPoint[m_currentWeaponType].y);
			}
			else
			{
				characterPointPositiion = sf::Vector2f(getPosition().x - m_weaponsStartShootingPoint[m_currentWeaponType].x, 
										  getPosition().y - m_weaponsStartShootingPoint[m_currentWeaponType].y);
			}
	

			sf::Vector2f shootingPoint;
	

			switch (m_currentCharacterAngle) {
			case WeaponAnimation::ANGLE::Angle0:
				shootingPoint = {  characterPointPositiion.x + dir * m_shootingPointsOffsets[m_currentWeaponType][m_currentCharacterAngle].x, 
									characterPointPositiion.y + m_shootingPointsOffsets[m_currentWeaponType][m_currentCharacterAngle].y };
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
		m_shooitngPointCenter.setPosition(m_shootingPointDynamic.getPosition().x, m_shootingPointDynamic.getPosition().y);
	}
}

