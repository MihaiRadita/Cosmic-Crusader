#include "stdafx.h"
#include "Creature.h"

//#include "game/Player.h"

#include "EnumMask.h"

#include "SceneManager.h"


namespace ratchet
{
	std::list<sf::Vector2f> Creature::GetTracePointsList()
	{
		return m_tracePointsList;
	}
	Creature::Creature(const CreatureConfig& config) : GameObject(config)
	{
		

		//Character Features
		m_movementSpeed = config.m_movingSpeed;
		m_jumpImpulse = config.m_jumpImpulse;
		m_bodShoulderOffset = config.m_bodShoulderOffset;

		m_health = config.m_health;
		m_maxHealth = config.m_maxHealth;
		m_HealthBarId = config.m_healthBarID;

		m_checkPointOffsetX = 0.0f;
		m_checkPointOffsetY = 0.0f;

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

		m_previousIndexTrace = m_currenIndexTrace;

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


		//Sounds
		m_creatureSoundLoop = config.m_creatureSoundLoop;
		m_creatureSoundVolume = config.m_creatureSoundVolume;

		m_creatureHurtSoundPath = config.m_creatureHurtSoundPath;
		m_creatureDeathSoundPath = config.m_creatureDeathSoundPath;
		m_creatureDeathFallSoundPath = config.m_creatureDeathFallSoundPath;
		m_creatureJumpSoundPath = config.m_creatureJumpSoundPath;
		m_creatureLandingSoundPath = config.m_creatureLandingSoundPath;
		m_creatureWalkSoundPath = config.m_creatureWalkSoundPath;


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
				
			case ANIMATION_STATE::DIE:
				m_animationList.emplace(ANIMATION_STATE::DIE, new AnimationDeath(m_spritePath, m_weaponTypeList));
				break;
			}
		}

		m_characterAnimSwitch = -1;

		setWeapon(m_currentEquippedWeaponIndex);

		/*m_characterShootingPosition = sf::CircleShape(0.05);
		m_characterShootingPosition.setFillColor(sf::Color::Yellow);
		m_characterShootingPosition.setPosition(getPosition().x, getPosition().y);

		m_shootingPointDynamic = sf::CircleShape(0.05);
		m_shootingPointDynamic.setFillColor(sf::Color::Blue);
		m_shootingPointDynamic.setOrigin(m_shootingPointDynamic.getRadius(), m_shootingPointDynamic.getRadius());
		m_shootingPointDynamic.setPosition(getPosition().x, getPosition().y);

		m_shooitngPointCenter = sf::CircleShape(0.02f);
		m_shooitngPointCenter.setFillColor(sf::Color::Red);
		m_shooitngPointCenter.setOrigin(m_shooitngPointCenter.getRadius(), m_shooitngPointCenter.getRadius());
		m_shooitngPointCenter.setPosition(m_shootingPointDynamic.getPosition().x, m_shootingPointDynamic.getPosition().y);*/

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
		if (!m_activeGameObject) return;


		checkCharacterGameOverTurned();
		updateDie();

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
				if (!m_isDeath)
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
			}

			if (m_input.isJump && isGrounded())
			{
				if (!m_isDeath)
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
			}
			if (m_input.isJump && isGrounded() && m_isMoving == true)
			{
				if (!m_isDeath)
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
			}

			if (isNoControlActive() && isGrounded() && m_isMoving == false && !m_isDeath)
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

			if (m_isDeath && isGrounded())
			{
				if (m_currentAnimationState != DIE)
				{
					m_currentAnimationState = DIE;

					if (m_currentWeaponType != Weapon::TYPE::None)
					{
						m_currentWeaponType = Weapon::TYPE::None;
						int index = static_cast<int>(m_currentWeaponType);

						setWeapon(index);
					}


 					switchAnimation();

					m_input.resetControls();
				}
			}

			m_characterAnimator->play(m_characterAnimator->getAbstractAnimation(), m_sprite, m_currentWeaponType, m_currentCharacterAngle, m_currentCharacterState);


			// Sync sprite position with collider

			if (m_collider)
			{
				auto position = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);

				// Sync sprite rotation with collider
				m_rotation = m_collider->getBody()->GetAngle() * (180.f / M_PI);
				m_sprite.setRotation(m_rotation);
			}

		}
		else if (m_faction == Faction::TEAM_1)
		{

			if (m_movementType == MovementType::GROUND)
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

				if (isNoControlActive() && isGrounded() && m_isMoving == false && !m_isDeath)
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
						if (isOnRecoil && m_isDeath)
						{
							isOnRecoil = false;
							return;
						}

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

				if (m_isDeath)
				{
					if (m_currentAnimationState != DIE)
					{
						m_currentAnimationState = DIE;

						switchAnimation();

						m_input.resetControls();
					}
				}

				m_characterAnimator->play(m_characterAnimator->getAbstractAnimation(), m_sprite, m_currentWeaponType, m_currentCharacterAngle, m_currentCharacterState);

				if (m_collider)
				{
					auto position = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);

					// Sync sprite rotation with collider
					m_rotation = m_collider->getBody()->GetAngle() * (180.f / M_PI);
					m_sprite.setRotation(m_rotation);
				}
			}
			else if (m_movementType == MovementType::AIR)
			{
				if (isNoControlActive() && m_isMoving == false && !m_isDeath)
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
						if (isOnRecoil && m_isDeath)
						{
							isOnRecoil = false;
							return;
						}

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

				if (m_isDeath)
				{
					if (m_currentAnimationState != DIE)
					{
						m_currentAnimationState = DIE;

						switchAnimation();

						m_input.resetControls();
					}
				}


				m_characterAnimator->play(m_characterAnimator->getAbstractAnimation(), m_sprite, m_currentWeaponType, m_currentCharacterAngle, m_currentCharacterState);

				if (m_collider)
				{
					auto position = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);

					// Sync sprite rotation with collider
					m_rotation = m_collider->getBody()->GetAngle() * (180.f / M_PI);
					m_sprite.setRotation(m_rotation);
				}
			}
		}
	}
	void Creature::updateJump()
	{
		if (m_isDeath && !isGrounded())
		{
			m_isMoving = false;
		}
	}
	void Creature::updateRunningJump()
	{
	}

	void Creature::updateWeaponSelection()
	{
		if (m_isDeath)
		{
			return;
		}

		if (m_currentEquippedWeaponIndex != m_input.weaponInputIndex)
		{
			m_currentEquippedWeaponIndex = m_input.weaponInputIndex;
			setWeapon(m_currentEquippedWeaponIndex);
		}
	}

	void Creature::updateShooting()
	{
		if (m_isDeath)
		{
			return;
		}

		if (m_mustSpawnBullet)
		{

			if (m_ownedWeaponList[m_currentEquippedWeaponIndex]->m_infiniteAmmo == false)
			{
				if (m_ownedWeaponList[m_currentEquippedWeaponIndex]->m_currentAmmo != 0)
				{
					m_ownedWeaponList[m_currentEquippedWeaponIndex]->Fire(m_currentFirePoint, m_currentFireRoationDegrees, m_currenFireDirectionNorm, m_facingRight);
#ifdef IS_RATCHET_DEBUG
					TRACE_CHANNEL("WEAPON_FIRE", "Must Spawn Bullet = false");
#endif	

					m_ownedWeaponList[m_currentEquippedWeaponIndex]->DecreaseAmmo();
				}
				m_mustSpawnBullet = false;
			}
			else
			{
				m_ownedWeaponList[m_currentEquippedWeaponIndex]->Fire(m_currentFirePoint, m_currentFireRoationDegrees, m_currenFireDirectionNorm, m_facingRight);
#ifdef IS_RATCHET_DEBUG
				TRACE_CHANNEL("WEAPON_FIRE", "Must Spawn Bullet = false");
#endif	
				m_mustSpawnBullet = false;
			}

		}
	}

	void Creature::updateTrace()
	{

	}

	void Creature::RestartObjectFeatures()
	{

	}

	void Creature::serialise(nlohmann::json& jsonFile)
	{
		 GameObject::serialise(jsonFile);

		 jsonFile["x"] = m_sprite.getPosition().x * 100;
		 jsonFile["y"] = m_sprite.getPosition().y * 100;

		 EnumMask<Weapon::TYPE> saveMask;

		for (auto& weapon : m_ownedWeaponList)
		{

			auto it = m_usableWeaponTypeList.find(weapon->m_weaponType);
			if (it != m_usableWeaponTypeList.end() && it->second)
			{
				saveMask.addValue(weapon->m_weaponType);

				auto* weaponObj = SceneManager::Get().FindObjectById(
					weapon->m_WeaponID,
					SceneManager::Get().GetLayerNameObjectByID(weapon->m_WeaponID)
				);

				if (weaponObj)
				{
					for (auto& prop : (*weaponObj)["properties"])
					{
						if (prop["name"] == "isWeaponAccesible")
						{
							auto& value = prop["value"];
							value = false;
							break;
						}
					}
				}
			}
		}

		for (auto& prop : jsonFile["properties"])
		{
			if (prop["name"] == "usableWeaponCheckListMask")
			{
				auto& value = prop["value"];
				value = saveMask.getRawValue();
				break;
			}
		}
	}

	void Creature::resetSerialise(nlohmann::json& originaljsonFile, nlohmann::json& jsonFile)
	{
		if (!originaljsonFile.contains("layers"))
		{
			std::cout << "WARNING: Scene has no layers << " << std::endl;
			return;
		}

		for (auto& layer : originaljsonFile["layers"])
		{
			auto& layerName = layer["name"];

			for (auto& obj : layer["objects"])
			{
				if (obj["name"] == jsonFile["name"])
				{
					jsonFile = obj;
					return;
				}
			}
		}
	}
		
	void Creature::invertCharacterMovingSpriteScale(int direction)
	{
		if (m_isDeath)
		{
			return;
		}

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

	void Creature::checkCharacterGameOverTurned()
	{
		auto* player = dynamic_cast<Player*>(this);
		auto* enemy = dynamic_cast<SelfControlledCreature*>(this);

		if (player)
		{
			if (player->m_isDeath)
			{
				if (m_currentAnimationState == ANIMATION_STATE::DIE)
				{
					if (m_characterAnimator->getAbstractAnimation()->isAnimationEnd())
					{
						Timer timer;
						while (SceneManager::Get().m_gameOver == false)
						{
							if (timer.GetElapsed().asSeconds() >= 1.2f)
							{
								SceneManager::Get().m_gameOver = true;
							}
						}
					}
				}
				
				if (SceneManager::Get().m_gameOver)
				{
					SceneManager::Get().RestartLevel();
					player->m_isDeath = false;
					player->m_shouldPlayDeathSound = false;
					player->m_isDeathFall = false;

					std::vector<Bullet*> bulletsToDestroy;

					for (auto* object : GameObject::s_gameObjects)
					{
						if (auto* bullet = dynamic_cast<Bullet*>(object))
						{
							bulletsToDestroy.push_back(bullet);
						}
					}

					for (auto* bullet : bulletsToDestroy)
					{
						bullet->DestroyGameObject();
					}

					for (auto* weapon : player->m_ownedWeaponList)
					{
						if (weapon->m_weaponType != Weapon::TYPE::None)
						{
							weapon->ClearBulletList();
						}
					}

					m_characterAnimator->getAbstractAnimation()->SetAnimationEnd(false);

					m_input.resetControls();
				}
				
			}

		}
		else if (enemy)
		{
			for (auto* object : s_gameObjects)
			{
				auto* playerTarget = dynamic_cast<Player*>(object);

				if(playerTarget)
				{
					if (playerTarget->m_isDeath)
					{
						for (auto* weapon : enemy->m_ownedWeaponList)
						{
							if (weapon->m_weaponType != Weapon::TYPE::None)
							{
								weapon->ClearBulletList();
							}
						}
					}
				}
			}
		}
	}

	void Creature::Die()
	{

	}

	void Creature::increaseHealth(float& health)
	{
		m_health += health;

		if (m_health > m_maxHealth)
		{
			m_health = m_maxHealth;
		}
	}

	void Creature::increaseAmmo(float& ammo, int& weponID)
	{
		for (auto* weapon : m_ownedWeaponList)
		{
			if (weapon->m_WeaponID == weponID)
			{

				if (weapon->m_infiniteAmmo == false)
				{
					weapon->m_currentAmmo += ammo;

					if (weapon->m_currentAmmo > weapon->m_maxAmmo)
					{
						weapon->m_currentAmmo = weapon->m_maxAmmo;
					}
				}
				break;
			}
		}
	}

	void Creature::restoreMaxHealth()
	{
		if (m_health < m_maxHealth)
		{
			m_health = m_maxHealth;
		}
	}

	void Creature::restoreMaxWeaponsAmmo()
	{
		for (auto* weapon : m_ownedWeaponList)
		{
			if (weapon->m_weaponType == Weapon::TYPE::None)
			{
				continue;
			}

			if (weapon->m_currentAmmo < weapon->m_maxAmmo)
			{
				weapon->m_currentAmmo = weapon->m_maxAmmo;
			}
		}
	}

	bool Creature::checkAnyWeaponAmmoNeedsRestore()
	{
		for (auto* weapon : m_ownedWeaponList)
		{
			if (weapon->m_weaponType == Weapon::TYPE::None)
			{
				continue;
			}

			if (weapon->m_currentAmmo < weapon->m_maxAmmo)
			{
				return true;
			}
		}
		return false;
	}

	void Creature::PostCosntructFixup()
	{
		if (m_collider) {
			m_collider->SetOwner(this); // now it's really Creature*
		}
	}

	void Creature::updateDie()
	{
		if (m_isDeath)
		{
			if (auto* player = dynamic_cast<Player*>(this))
			{
				player->Die();
			}
			else if (auto* enemy = dynamic_cast<SelfControlledCreature*>(this))
			{
				enemy->Die();
			}
		}
		
		
	}

	void Creature::Start()
	{

		auto* uiBarConfig = PrefabAssets::Get().GetUIBarConfig(m_HealthBarId);

		if (uiBarConfig)
		{
			m_uiHealthBar = new UIBar(*uiBarConfig);
			s_gameObjects.push_back(m_uiHealthBar);
			m_uiHealthBar->Start();
		}

		PostCosntructFixup();

		if (!m_hurtSoundBuffer.loadFromFile(m_creatureHurtSoundPath))
		{
			std::cout << "Sound did not load!" << std::endl;
		}

		if (!m_deathSoundBuffer.loadFromFile(m_creatureDeathSoundPath))
		{
			std::cout << "Sound did not load!" << std::endl;
		}

		if (!m_deathFallSoundBuffer.loadFromFile(m_creatureDeathFallSoundPath))
		{
			std::cout << "Sound did not load!" << std::endl;
		}

		if (!m_jumpSoundBuffer.loadFromFile(m_creatureJumpSoundPath))
		{
			std::cout << "Sound did not load!" << std::endl;
		}

		if (!m_landingSoundBuffer.loadFromFile(m_creatureLandingSoundPath))
		{
			std::cout << "Sound did not load!" << std::endl;
		}

		if (!m_walkSoundBuffer.loadFromFile(m_creatureWalkSoundPath))
		{
			std::cout << "Sound did not load!" << std::endl;
		}

		m_hurtSound = sf::Sound();
		m_hurtSound.setBuffer(m_hurtSoundBuffer);
		m_hurtSound.setLoop(m_creatureSoundLoop);
		m_hurtSound.setVolume(m_objectSoundEffectVolume);


		m_deathSound = sf::Sound();
		m_deathSound.setBuffer(m_deathSoundBuffer);
		m_deathSound.setLoop(m_creatureSoundLoop);
		m_deathSound.setVolume(m_objectSoundEffectVolume);

		m_deathFallSound = sf::Sound();
		m_deathFallSound.setBuffer(m_deathFallSoundBuffer);
		m_deathFallSound.setLoop(m_creatureSoundLoop);
		m_deathFallSound.setVolume(m_objectSoundEffectVolume);

		m_jumpSound = sf::Sound();
		m_jumpSound.setBuffer(m_jumpSoundBuffer);
		m_jumpSound.setLoop(m_creatureSoundLoop);
		m_jumpSound.setVolume(m_objectSoundEffectVolume);

		m_landingSound = sf::Sound();
		m_landingSound.setBuffer(m_landingSoundBuffer);
		m_landingSound.setLoop(m_creatureSoundLoop);
		m_landingSound.setVolume(m_objectSoundEffectVolume);

		m_walkSound = sf::Sound();
		m_walkSound.setBuffer(m_walkSoundBuffer);
		m_walkSound.setLoop(m_creatureSoundLoop);
		m_walkSound.setVolume(m_objectSoundEffectVolume);

	


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
	void Creature::TakeDamage(float& damage)
	{
		if (m_isInvlunerbleForTesting)
			return;

		if (m_isInvulnerable)
			return;
		m_health -= damage;

		std::cout << "Character health: " << m_health << std::endl;

		if (auto* player = dynamic_cast<Player*>(this))
		{
			m_isInvulnerable = true;
			player->GettimeBeingInvulnerable().Restart();
		}

		if (m_health <= 0.0f)
		{
			m_health = 0.0f;

			if (!m_isDeath)
			{
				m_isDeath = true;
				m_isInvulnerable = false;
			}
		}
		else
		{
			float volume = SceneManager::Get().GetSoundEffectsVolume();
			m_hurtSound.setVolume(volume);
			m_hurtSound.play();
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
			newWeapon->m_maxAmmo = config->m_MaxAmmo;
			newWeapon->m_currentAmmo = config->m_MaxAmmo;
			newWeapon->m_infiniteAmmo = config->m_infiniteAmmo;
			newWeapon->m_ammoDecrease = config->m_ammoDecrease;
			newWeapon->m_weaponDamage = config->m_damage;
			shootingPointXOffset = config->m_weaponShootPointOffsetX;
			shootingPointYOffset = config->m_weaponShootPointOffsetY;
			newWeapon->m_WeaponID = config->m_objectID;
			newWeapon->m_bulletID = config->m_bulletID;
			newWeapon->m_bulletPoolIncrementation = config->m_bulletPoolIncrementation;

			if (!newWeapon->m_weaponSoundBuffer.loadFromFile(config->m_weaponSoundPath))
			{
				std::cout << "Weapon sound did not load!" << std::endl;
			}
			
			newWeapon->m_weaponSound = sf::Sound();
			newWeapon->m_weaponSound.setBuffer(newWeapon->m_weaponSoundBuffer);


			newWeapon->m_weaponSoundVolume = SceneManager::Get().m_soundEffectsVolume;

			newWeapon->m_weaponSoundLoop = config->m_weaponSoundLoop;

			newWeapon->m_weaponSound.setVolume(newWeapon->m_weaponSoundVolume);

			newWeapon->m_weaponSound.setLoop(newWeapon->m_weaponSoundLoop);


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

			if (m_movementType == MovementType::AIR)
			{
				dir;
			}

			if (dir < 0.f)
			{


				auto* drone = dynamic_cast<SelfControlledCreature*>(this);


				if (drone && drone->m_enemyType == EnemyType::Flying)
				{
					
				}

				characterPointPositiion = sf::Vector2f(getPosition().x + m_weaponsStartShootingPoint[m_currentWeaponType].x, getPosition().y - m_weaponsStartShootingPoint[m_currentWeaponType].y);


			}
			else
			{
				auto* drone = dynamic_cast<SelfControlledCreature*>(this);


				if (drone && drone->m_enemyType == EnemyType::Flying)
				{
					
				}

				characterPointPositiion = sf::Vector2f(getPosition().x - m_weaponsStartShootingPoint[m_currentWeaponType].x,
					getPosition().y - m_weaponsStartShootingPoint[m_currentWeaponType].y);
			}


			sf::Vector2f shootingPoint;


			switch (m_currentCharacterAngle) {
			case WeaponAnimation::ANGLE::Angle0:
				shootingPoint = { characterPointPositiion.x + dir * m_shootingPointsOffsets[m_currentWeaponType][m_currentCharacterAngle].x,
									characterPointPositiion.y + m_shootingPointsOffsets[m_currentWeaponType][m_currentCharacterAngle].y };
				break;
			case WeaponAnimation::ANGLE::Angle45:
				shootingPoint = { characterPointPositiion.x + dir * m_shootingPointsOffsets[m_currentWeaponType][m_currentCharacterAngle].x,
								characterPointPositiion.y - m_shootingPointsOffsets[m_currentWeaponType][m_currentCharacterAngle].y };
				break;

			case WeaponAnimation::ANGLE::Angle90:


				shootingPoint = { characterPointPositiion.x, characterPointPositiion.y - m_shootingPointsOffsets[m_currentWeaponType][m_currentCharacterAngle].y };
				break;
			case WeaponAnimation::ANGLE::AngleMinus45:

				shootingPoint = { characterPointPositiion.x + dir * m_shootingPointsOffsets[m_currentWeaponType][m_currentCharacterAngle].x,
								characterPointPositiion.y + m_shootingPointsOffsets[m_currentWeaponType][m_currentCharacterAngle].y };
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

