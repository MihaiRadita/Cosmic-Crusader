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

		m_minFollowHeightOffset = config.m_minFollowHeightOffset;
		m_minCeilingDistance = config.m_minCeilingDistance;
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
			sf::Vector2f diff = target->getPosition() - this->getPosition();
			float length = std::sqrt(diff.x * diff.x + diff.y * diff.y);

			m_isAttacking = false;
			if (length <= m_targetMaxDistanceAttackX)
			{
				m_isAttacking = true;
			}
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
								else if (auto* circleCollider = dynamic_cast<CircleCollider*>(m_collider))
								{
									auto* configColliderPtr = config.m_colliderConfig;

									circleCollider->m_body->SetTransform(b2Vec2(config.position.x, config.position.y), 0.0f);

									circleCollider->m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
									circleCollider->m_body->SetAngularVelocity(0.0f);

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
					auto* player = dynamic_cast<Player*>(m_target);

					if (!player)
					{
						return;
					}


					sf::Vector2f baseTarget = player->getPosition();
					auto getPerpendicular = [&](sf::Vector2f tar) { 
						sf::Vector2f diff = tar - m_position;
						float length = std::sqrt(diff.x * diff.x + diff.y * diff.y);
						sf::Vector2f direction(0.f, 0.f);
						if (length != 0.f)
						{
							direction = diff / length;
						}
						return sf::Vector2f(-direction.y, direction.x); // perpendicular
					};

					auto baseTargetPerpendicular = getPerpendicular(baseTarget);
					float selfRadius = circleCollider->getGlobalRadius();
					float playerRadius = selfRadius;

					if (auto* playerCollider = player->m_collider)
					{
						if (auto* capsuleCollider = dynamic_cast<CapsuleCollider*>(playerCollider))
						{
							playerRadius = capsuleCollider->getGlobalRadius();
						}
					}
					float minRadius = std::min(selfRadius, playerRadius);

					sf::Vector2f centerStart = m_position;
					sf::Vector2f rightStart = m_position + baseTargetPerpendicular * minRadius;
					sf::Vector2f leftStart = m_position - baseTargetPerpendicular * minRadius;

					sf::Vector2f centerEnd = baseTarget;
					sf::Vector2f rightEnd = baseTarget + baseTargetPerpendicular * minRadius;
					sf::Vector2f leftEnd = baseTarget - baseTargetPerpendicular * minRadius;


					m_canSeePlayerCenter = circleCollider->performFollowTargetRayCast(centerStart, centerEnd);
					m_canSeeRightSide = circleCollider->performFollowTargetRayCast(rightStart, rightEnd);
					m_canSeeLeftSide = circleCollider->performFollowTargetRayCast(leftStart, leftEnd);

		
					if (m_isAttacking && m_canSeePlayerCenter && m_canSeeRightSide && m_canSeeLeftSide)
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

					if (m_canSeePlayerCenter && m_canSeeRightSide && m_canSeeLeftSide)
					{
						if (!m_targetPointsFollow.empty())
						{
							m_targetPointsFollow.clear();
							m_currentTargetPointIndex = 0;
						}

						sf::Vector2f target = baseTarget;

						// Swap target to favoured spot above the player if possible.
						auto isTooCloseToCeiling = circleCollider->performUpPlatformRayCast(m_sprite);
						if (!isTooCloseToCeiling)
						{
							auto favouredSpot = sf::Vector2f(baseTarget.x, baseTarget.y - m_minFollowHeightOffset);

							auto targetPerpendicular = getPerpendicular(baseTarget);
							sf::Vector2f targetCenterEnd = baseTarget;
							sf::Vector2f targetRightEnd = baseTarget + targetPerpendicular * selfRadius;
							sf::Vector2f targetLeftEnd = baseTarget - targetPerpendicular * selfRadius;

							sf::Vector2f favouredSpotCenterEnd = favouredSpot;
							sf::Vector2f favouredSpotRightEnd = favouredSpot + targetPerpendicular * selfRadius;
							sf::Vector2f favouredSpotLeftEnd = favouredSpot - targetPerpendicular * selfRadius;

							bool favouredSpotIsInLoSOfPlayer =
								circleCollider->performFollowTargetRayCast(targetCenterEnd, favouredSpotCenterEnd) ||
								circleCollider->performFollowTargetRayCast(targetRightEnd, favouredSpotRightEnd) ||
								circleCollider->performFollowTargetRayCast(targetLeftEnd, favouredSpotLeftEnd);

							if (favouredSpotIsInLoSOfPlayer)
							{
								sf::Vector2f potentialCeilingCenterEnd = favouredSpotCenterEnd + sf::Vector2f(0.0f, -1.0f) * m_minFollowHeightOffset;
								sf::Vector2f potentialCeilingRightEnd = favouredSpotCenterEnd + sf::Vector2f(1.0f, 0.0f) * selfRadius + sf::Vector2f(0.0f, -1.0f) * m_minFollowHeightOffset;
								sf::Vector2f potentialCeilingLeftEnd = favouredSpotCenterEnd - sf::Vector2f(1.0f, 0.0f) * selfRadius + sf::Vector2f(0.0f, -1.0f) * m_minFollowHeightOffset;

								bool favouredSpotIsTooCloseToCeiling =
									circleCollider->performFollowTargetRayCast(favouredSpotCenterEnd, potentialCeilingCenterEnd) ||
									circleCollider->performFollowTargetRayCast(favouredSpotRightEnd, potentialCeilingRightEnd) ||
									circleCollider->performFollowTargetRayCast(favouredSpotLeftEnd, potentialCeilingLeftEnd);

								if (!favouredSpotIsTooCloseToCeiling)
								{
									target = favouredSpot;
								}
							}
						}

						sf::Vector2f directDiffToPlayer = target - m_position;

						float directLengthToPlayer = std::sqrt(directDiffToPlayer.x * directDiffToPlayer.x + directDiffToPlayer.y * directDiffToPlayer.y);

						sf::Vector2f directDirToPlayer(0.f, 0.f);

						if (directLengthToPlayer != 0.f)
						{
							directDirToPlayer.x = directDiffToPlayer.x / directLengthToPlayer;
							directDirToPlayer.y = directDiffToPlayer.y / directLengthToPlayer;
						}

						m_input.x = directDirToPlayer.x;
						m_input.y = directDirToPlayer.y;
					}
					else 
					{
						if (player)
						{
							if (m_targetPointsFollow.empty())
							{
								sf::Vector2f startPathPoint{};
								size_t startPointIndex = 0;
								bool found = false;

								const auto& trace = player->m_tracePointsList;

								if (trace.empty())
								{
									return;
								}


								const size_t traceSize = trace.size();

								m_targetPointsFollow.clear();
								for (auto it = trace.rbegin(); it != trace.rend(); ++it)
								{
									sf::Vector2f targetPoint = *it;
									auto targetPointPerpendicular = getPerpendicular(targetPoint);
									sf::Vector2f targetPointCenterEnd = targetPoint;
									sf::Vector2f targetPointRightEnd = targetPoint + targetPointPerpendicular * selfRadius;
									sf::Vector2f targetPointLeftEnd = targetPoint - targetPointPerpendicular * selfRadius;

									m_targetPointsFollow.push_back(targetPoint);

									bool blocked =
										circleCollider->performFollowTargetRayCast(centerStart, targetPointCenterEnd) ||
										circleCollider->performFollowTargetRayCast(rightStart, targetPointRightEnd) ||
										circleCollider->performFollowTargetRayCast(leftStart, targetPointLeftEnd);

									if (blocked)
									{
										continue;
									}
									else
									{
										std::reverse(m_targetPointsFollow.begin(), m_targetPointsFollow.end());
										m_currentTargetPointIndex = 0;
										break;
									}
							
								}
							}
							else
							{
								sf::Vector2f pointTarget = m_targetPointsFollow[m_currentTargetPointIndex];


								auto pointTargetPerpendicular = getPerpendicular(pointTarget);
								sf::Vector2f pointTargetCenterEnd = pointTarget;
								sf::Vector2f pointTargetRightEnd = pointTarget + pointTargetPerpendicular * selfRadius;
								sf::Vector2f pointTargetLeftEnd = pointTarget - pointTargetPerpendicular * selfRadius;

								bool blocked =
									circleCollider->performFollowTargetRayCast(centerStart, pointTargetCenterEnd) ||
									circleCollider->performFollowTargetRayCast(rightStart, pointTargetRightEnd) ||
									circleCollider->performFollowTargetRayCast(leftStart, pointTargetLeftEnd);

								bool reset = false;
								if (blocked)
								{
									reset = true;
								}
								else
								{
									sf::Vector2f diffPoint = pointTarget - m_position;
									float lengthPoint = std::sqrt(diffPoint.x * diffPoint.x + diffPoint.y * diffPoint.y);

									sf::Vector2f direction(0.f, 0.f);

									if (lengthPoint > 0.0001f)
									{
										direction = diffPoint / lengthPoint;
									}

									m_input.x = direction.x;
									m_input.y = direction.y;

									if (lengthPoint <= circleCollider->getGlobalRadius())
									{
										m_currentTargetPointIndex++;

										if (m_currentTargetPointIndex >= m_targetPointsFollow.size())
										{
											reset = true;
										}
									}
								}

								if (reset)
								{
									m_targetPointsFollow.clear();
									m_currentTargetPointIndex = 0;
								}
							}
						}
					}
					
				}
			}
		}
		else
		{
			m_input.x = 0;
			m_input.y = 0;
			m_input.isJump = false;
			m_targetPointsFollow.clear();
			m_currentTargetPointIndex = 0;

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

		float length = std::sqrt(diff.x * diff.x + diff.y * diff.y);

		m_isTargetDetected = false;
		if (length <= m_targetMaxDistanceDetectionX)
		{
			m_isTargetDetected = true;
		}
	}

	void SelfControlledCreature::render(sf::RenderTarget& target)
	{
		GameObject::render(target);
		target.draw(m_characterShootingPosition);
		target.draw(m_shootingPointDynamic);
		target.draw(m_shooitngPointCenter);


		size_t index = 0ull;
		for (auto it = m_targetPointsFollow.begin(), prevIt = m_targetPointsFollow.begin(); it != m_targetPointsFollow.end(); it++)
		{
			bool drawLineFromOldToCurrentPoint = false;

			sf::CircleShape circle(0.1f);
			circle.setPosition(*it);
			if (index == m_currentTargetPointIndex)
			{
				circle.setFillColor(sf::Color::Cyan);
			}
			else
			{
				circle.setFillColor(sf::Color::Yellow);
			}

			if (prevIt != it)
			{
				drawLineFromOldToCurrentPoint = true;
			}

			if (drawLineFromOldToCurrentPoint)
			{
				sf::Vertex line[] = { sf::Vertex(*prevIt, sf::Color::Cyan), sf::Vertex(*it, sf::Color::Cyan)};
				target.draw(line, 2, sf::Lines);

				prevIt++;
			}

			target.draw(circle);
			index++;
		}

	}
}
