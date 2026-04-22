#include "stdafx.h"
#include "SelfControlledCreature.h"

#include "SceneManager.h"

namespace ratchet
{

	ratchet::SelfControlledCreature::SelfControlledCreature(const SelfControlledCreatureConfig& config) : Creature(config)
	{

		m_targetMaxDistanceDetectionX = config.m_targetMaxDistanceDetectionX;
		m_targetMaxDistanceDetectionY = config.m_targetMaxDistanceDetectionY;
		m_targetMaxDistanceLoseX = config.m_targetMaxDistanceLoseX;
		m_targetMaxDistanceLoseY = config.m_targetMaxDistanceLoseY;
		m_targetMaxDistanceAttackX = config.m_targetMaxDistanceAttackX;
		m_targetMaxDistanceAttackY = config.m_targetMaxDistanceAttackY;

		m_enemyType = config.m_enemyType;
		m_objectId = config.m_objectID;

		m_objectLayerName = config.m_objectLayerName;

		m_flySpeed = config.m_flySpeed;
	}
	SelfControlledCreature::~SelfControlledCreature()
	{
		if (m_collider)
		{
			delete m_collider;
			m_collider = nullptr;
		}
	}
	void SelfControlledCreature::checkTargetToAttack(Creature* target)
	{
		float absX = std::abs(target->getPosition().x - getPosition().x);
		float absY = std::abs(target->getPosition().y - getPosition().y);

		if (m_enemyType == EnemyType::Ground)
		{
			m_isAttacking = (absX <= m_targetMaxDistanceAttackX);
		}
		else if (m_enemyType == EnemyType::Flying)
		{
			m_isAttacking = (absX <= m_targetMaxDistanceAttackX);
		}

	}

	void SelfControlledCreature::handleSelfCreatureEvent()
	{
		if (SceneManager::Get().m_isPaused)
		{
			m_fireCooldown.Freeze();
		}
		else if (!SceneManager::Get().m_isPaused)
		{
			m_fireCooldown.Resume();
		}
	}

	void SelfControlledCreature::Die()
	{

		if (m_shouldPlayDeathSound)
		{
			return;
		}

		m_isAttacking = false;

		float volume = SceneManager::Get().GetSoundEffectsVolume();
		m_deathSound.setVolume(volume);
		m_deathSound.play();

		m_shouldPlayDeathSound = true;
	


		GameObject::DestroyCollider();

		for (size_t i = 0; i < GameObject::s_gameObjects.size(); i++)
		{
			if (GameObject::s_gameObjects[i] == this)
			{
				SceneManager::Get().m_characters_destroyedID_index.insert({ m_objectId, i });
				break;
			}
		}
	}
	void SelfControlledCreature::canJumpOver()
	{
		if (m_collider && !m_collider->m_skipRaycastThisFrame)
		{
			m_collider->m_collierFacingDirectionX = m_facingRight ? 1.0f : -1.0f;
			m_canJumpOver = m_collider->performJumpOverPlatformsRaycast(m_sprite, m_collider->m_collierFacingDirectionX);
		}
		else
		{
			m_canJumpOver = false;
			m_collider->m_skipRaycastThisFrame = false;
		}
	}
	void SelfControlledCreature::isFallingRisk()
	{
		if (m_collider && !m_collider->m_skipRaycastThisFrame)
		{
			m_collider->m_collierFacingDirectionX = m_facingRight ? 1.0f : -1.0f;
			m_isFallingRisk = m_collider->performCheckFallingRiskRaycast(m_sprite, m_collider->m_collierFacingDirectionX);
		}
		else
		{
			m_isFallingRisk = false;
			m_collider->m_skipRaycastThisFrame = false;
		}
	}
	void SelfControlledCreature::SetTarget(Faction& faction)
	{
		for (auto* obj : s_gameObjects)
		{
			if (obj != this)
			{
				if (faction != Faction::FACTION_UNKNOWN && obj->m_faction != Faction::FACTION_UNKNOWN)
				{
					if (faction != obj->m_faction)
					{
						m_target = (Creature*)obj;
						break;
					}
				}
			}
		}
	}
	void SelfControlledCreature::PostCosntructFixup()
	{
		if (m_collider)
		{
			m_collider->SetOwner(this);
		}
	}
	void SelfControlledCreature::computeAimBulletRotation()
	{
		auto enemyType = m_enemyType;

		sf::Vector2f firePoint = m_currentFirePoint;
		sf::Vector2f targetPos = m_target->getPosition();

		sf::Vector2f direction = targetPos - firePoint;
		sf::Vector2f directionNormalised = sf::Vector2f(0.0f, 0.0f);
		calculateNormalised(direction.x, direction.y, directionNormalised.x, directionNormalised.y);

		float angleRad = std::atan2(directionNormalised.y, directionNormalised.x);
		float angleDeg = angleRad * 180.f / M_PI;

		m_currentFireRotationRadians = angleRad;
		m_currentFireRoationDegrees = angleDeg;
		m_currenFireDirectionNorm = directionNormalised;
	}
	void SelfControlledCreature::RestartObjectFeatures()
	{
		const auto& sceneFiles = SceneManager::Get().GetSceneFiles();
		std::string sceneName = SceneManager::Get().GetSceneFiles()[SceneManager::Get().GetCurrentScene()];
		const auto& allScenes = SceneManager::Get().GetAllScenesFile();

		if (sceneName == "Main Menu")
		{
			return;
		}

		if (!allScenes.contains("scenes")) {
			std::cout << "ERROR: GameScenes.json does not contain 'Scenes' key\n";
			return;
		}

		auto& scenesNode = allScenes["scenes"];
		if (!scenesNode.contains(sceneName)) {
			std::cout << "ERROR: Scene not found in GameScenes.json: " << sceneName << "\n";
			return;
		}

		auto& sceneJson = scenesNode[sceneName];

		if (!sceneJson.contains("layers") || !sceneJson["layers"].is_array()) {
			std::cout << "WARNING: Scene has no layers or layers is not an array: " << sceneName << "\n";
			return;
		}

		for (auto& layer : sceneJson["layers"])
		{
			const auto& validLayer = layer.contains("objects");
			if (!validLayer) continue;

			const auto& layerName = layer["name"].get<std::string>();

			if (layerName == "Enemies")
			{
				for (auto& obj : layer["objects"])
				{
					std::string name = obj["name"];


					if (name == m_objectLayerName)
					{
						int objID = obj["id"];

						if (objID == m_objectId)
						{
							auto config = SelfControlledCreatureConfig();
							auto* configPtr = &config;

							if (config.deserialise(obj))
							{
								m_currentAnimationState = ANIMATION_STATE::IDLE;
								m_health = config.m_health;
								//m_position = sf::Vector2f(config.position.x, config.position.y);


								if (auto* capsuleCollider = dynamic_cast<CapsuleCollider*>(m_collider))
								{
									auto* configColliderPtr = config.m_colliderConfig;

									capsuleCollider->m_body->SetTransform(b2Vec2(config.position.x, config.position.y), 0.0f);

									capsuleCollider->m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
									capsuleCollider->m_body->SetAngularVelocity(0.0f);

									setPosition(sf::Vector2f(config.position.x, config.position.y));
								}
							}
						}
						break;
					}
				}
			}
		}
	}
	void SelfControlledCreature::Start()
	{
		PostCosntructFixup();
		SetTarget(m_faction);

		Creature::Start();
	}

	void SelfControlledCreature::handleEvent()
	{
		if (m_isDeath)
		{
			m_input.m_isFiring = false;
			return;
		}
		if (m_target->m_isDeath)
		{
			if (m_isAttacking)
			{
				m_isAttacking = false;
				m_input.m_isFiring = false;
			}
			return;
		}

		handleSelfCreatureEvent();
		detectTarget(m_target);

		if (m_isTargetDetected)
		{
			TRACE_CHANNEL("AI_TARGETING", "Enemy detects target(PLAYER)!");
			m_facingRight = !m_isTagetBehindCharacter;
			invertCharacterMovingSpriteScale(m_facingRight ? 1.0f : -1.0f);
			checkTargetToAttack(m_target);
			isFallingRisk();
			canJumpOver();

			if (m_movementType == MovementType::GROUND)
			{
				if (m_isAttacking)
				{
					m_input.x = 0.f;
					m_input.isJump = false;
					if (!m_waitTostartAttack)
					{
						m_fireCooldown.m_clock.restart();
						m_waitTostartAttack = true;
						m_input.m_isFiring = false;
					}
					else if (m_fireCooldown.m_clock.getElapsedTime().asSeconds() >= m_fireRate)
					{
						m_input.m_isFiring = true;
					}
				}
				else
				{
					if (m_input.m_isFiring && m_currentCharacterState == WeaponAnimation::STATE::Recoil)
					{
						m_currentCharacterState = WeaponAnimation::STATE::Aim;
						m_input.m_isFiring = false;
					}
					m_waitTostartAttack = false;
					m_fireCooldown.m_clock.restart();

					if (m_canJumpOver)
					{
						m_input.isJump = m_isGround;
					}
					else
					{
						m_input.isJump = false;
					}
					if (m_isFallingRisk)
					{
						m_input.x = m_facingRight ? 1.f : -1.f;
					}
					else
					{
						m_input.x = 0.f;
					}
				}
			}
			else if (m_movementType == MovementType::AIR)
			{
				

				if (auto* circleCollider = dynamic_cast<CircleCollider*>(m_collider))
				{

					const sf::Vector2f& targetPosition = m_target->getPosition();

		
					if (m_isAttacking)
					{
						m_input.x = 0.f;
						m_input.y = 0.f;

						if (!m_waitTostartAttack)
						{
							m_fireCooldown.m_clock.restart();
							m_waitTostartAttack = true;
							m_input.m_isFiring = false;
						}
						else if (m_fireCooldown.m_clock.getElapsedTime().asSeconds() >= m_fireRate)
						{
							m_input.m_isFiring = true;
						}

						return;
					}

					if (m_input.m_isFiring &&
						m_currentCharacterState == WeaponAnimation::STATE::Recoil)
					{
						m_currentCharacterState = WeaponAnimation::STATE::Aim;
						m_input.m_isFiring = false;
					}

					m_waitTostartAttack = false;
					m_fireCooldown.m_clock.restart();

					bool canSeePlayer =
						circleCollider->performFollowTargetRayCast(m_position, targetPosition);

					if (!canSeePlayer)
					{
						m_input.x = 0.f;
						m_input.y = 0.f;
						return;
					}


					sf::Vector2f toTarget = targetPosition - m_position;

					float moveX = toTarget.x;

					float minY = targetPosition.y + m_minFollowHeightOffset;

					float moveY = 0.f;

					
					if (m_position.y > minY)
					{
						moveY = -1.f;
					}
					else if (m_position.y < targetPosition.y - m_minFollowHeightOffset)
					{
						moveY = 1.f;
					}


					sf::Vector2f direction(moveX, moveY);

					float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

					if (length != 0.f)
						direction /= length;

					m_input.x = direction.x;
					m_input.y = direction.y;
			
				}
			}
		}
		else
		{
			m_input.x = 0;
			m_input.y = 0;
			m_input.isJump = false;
			if (m_input.m_isFiring && m_currentCharacterState == WeaponAnimation::STATE::Recoil)
			{
				m_currentCharacterState = WeaponAnimation::STATE::Aim;
			}
			m_input.m_isFiring = false;
			m_waitTostartAttack = false;
			m_fireCooldown.m_clock.restart();
		}

		if (m_canJumpOver)
		{
			TRACE_CHANNEL("AI_JUMP_OVER_PLATFORMS", "ENEMY CAN JUMP OVER PLATFORMS!");
		}
		else
		{
			TRACE_CHANNEL("AI_JUMP_OVER_PLATFORMS", "ENEMY CAN NOT JUMP OVER PLATFORMS!");
		}
	}
	void SelfControlledCreature::update()
	{

		if (!m_activeGameObject) return;

		if (SceneManager::Get().m_isPaused)
			m_fireCooldown.Freeze();
		else
			m_fireCooldown.Resume();

		if (!m_isDeath)
		{
			if (m_collider && !m_collider->m_skipRaycastThisFrame)
				m_isGround = m_collider->performGroundRayCast(m_sprite);
			else
			{
				m_isGround = false;
				if (m_collider)
					m_collider->m_skipRaycastThisFrame = false;
			}
		}

		handleEvent();


		Creature::update(); 

		if (m_isDeath && m_currentAnimationState == ANIMATION_STATE::DIE)
		{

			if (auto* deathAnimation = dynamic_cast<AnimationDeath*>(m_characterAnimator->getAbstractAnimation()))
			{
				if (deathAnimation->isAnimationEnd())
				{
					GameObject::DestroyGameObject();
					return;
				}
			}

		}
	}

	void SelfControlledCreature::updateMovement()
	{

		m_isMoving = false;

		bool changeX = false;
		bool changeY = false;

		float xVelocity = 0.0f;
		float yVelocity = 0.0f;

		if (m_movementType == MovementType::GROUND)
		{
			//
			if (m_input.x != 0.f)
			{
				m_isMoving = true;

				changeX = true;
				xVelocity = m_movementSpeed * m_input.x;

				if (m_isGround)
				{
					if (m_walkTimerSound.GetElapsed().asSeconds() >= 0.3f)
					{
						float volume = SceneManager::Get().GetSoundEffectsVolume();
						m_walkSound.setVolume(volume);
						m_walkSound.play();
						m_walkTimerSound.Restart();
					}
				}
				else
				{
					m_walkTimerSound.Restart();
				}
			}

			if (m_input.isJump && isGrounded())
			{
				m_isMoving = true;

				changeY = true;
				yVelocity = m_jumpImpulse;
			}

			if (m_collider)
			{
				m_collider->applyMovement(changeX, xVelocity, changeY, yVelocity);
			}
		}
		else if (m_movementType == MovementType::AIR)
		{
		

			float xInput = m_input.x;
			float yInput = m_input.y;

			xVelocity = m_movementSpeed * xInput;
			yVelocity = m_flySpeed * yInput;

			changeX = (xInput != 0.f);
			changeY = (yInput != 0.f);

			if (changeX || changeY)
			{
				m_isMoving = true;

				if (m_walkTimerSound.GetElapsed().asSeconds() >= 0.3f)
				{
					float volume = SceneManager::Get().GetSoundEffectsVolume();
					m_walkSound.setVolume(volume);
					m_walkSound.play();
					m_walkTimerSound.Restart();
				}
			}
			else
			{
				m_walkTimerSound.Restart();
			}

			if (m_collider)
			{
				m_collider->applyMovement(changeX, xVelocity, changeY, yVelocity);
			}
		}

		
		if (m_collider)
		{
			b2Vec2 pos = m_collider->getBody()->GetPosition();

			m_sprite.setPosition(pos.x, pos.y);
			m_rotation = m_collider->getBody()->GetAngle() * (180.f / M_PI);
			m_sprite.setRotation(m_rotation);

			setPosition(sf::Vector2f(pos.x, pos.y));
		}
		
	}
	void SelfControlledCreature::detectTarget(Creature* target)
	{
		sf::Vector2f diff = target->getPosition() - this->getPosition();

		float absX = std::abs(diff.x);
		float absY = std::abs(diff.y);

		m_isTagetBehindCharacter = (diff.x < 0.0f);

		m_isTargetDetected =
			(absX <= m_targetMaxDistanceDetectionX &&
				absY <= m_targetMaxDistanceDetectionY);
	}

	void SelfControlledCreature::render(sf::RenderTarget& target)
	{
		GameObject::render(target);
		target.draw(m_characterShootingPosition);
		target.draw(m_shootingPointDynamic);
		target.draw(m_shooitngPointCenter);
	}
}
