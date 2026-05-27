#include "stdafx.h"
#include "Bullet.h"

#include "SceneManager.h"

namespace ratchet
{
	Bullet::Bullet()
	{
	}

	Bullet::Bullet(const BulletConfig& config) : GameObject(config)
	{
		m_damage = config.m_damage;
		m_ammo = config.m_ammo;
		m_bulletSpeed = config.m_BulletSpeed;
		m_bulletLifeLimit = config.m_bulletLifeLimit;

		if (m_bulletBasicTexture.loadFromFile(m_startSpritePath) == false)
		{
#ifdef IS_RATCHET_DEBUG
			TRACE_CHANNEL("GAMEOBJECT_INIT", "ERROR::PLAYER COULD NOT LOAD THE TEXTURE SHEET");
#endif
		}



		m_bulletType = config.m_bulletType;
		m_explosionPositionOffset = config.m_explosionPositionOffset;

		m_explosionPositionOffset = 0.7;

		m_bulletExplosionPath = config.m_bulletExplosionPath;
		m_isBulletExploding = false;
		m_isExpplosionAnimationTrasition = true;
		m_currenExplosionIndex = 0;
		m_endExplosionAnimation = false;
		m_explosionHasDamaged = false;
		m_explosioTochTarget = false;

		m_bulletTimer.Restart();

		m_explosionAnimationTimer.Restart();
		setOrignAtCenter();

		if (m_bulletType == BulletType::Explosive)
		{
			m_currenExplosionAnimationSprite.setPosition(m_position.x, m_position.y);
			m_currenExplosionAnimationSprite.setRotation(m_rotation);
			m_currenExplosionAnimationSprite.setScale(m_scale.x, m_scale.y);
		}

		buildExplosionAnimation();

		PostCosntructFixup();
	}

	Bullet::~Bullet()
	{

	}

	void Bullet::setActive(bool active)
	{
		GameObject::setActive(active);

		m_bulletTimer.Restart();
	}

	void Bullet::PostCosntructFixup()
	{
		if (m_collider) {
			m_collider->SetOwner(this); // now it's really Creature*
		}
	}

	void Bullet::drawExplosionArea(sf::Vector2f& position, float& radius, sf::RenderTarget& target)
	{
		sf::CircleShape shape;

		shape.setRadius(radius);
		shape.setOrigin(radius, radius);   
		shape.setPosition(position);       

		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineThickness(0.2f);
		shape.setOutlineColor(sf::Color::Green);

		target.draw(shape);

	}

	void Bullet::update()
	{

		if (!m_activeGameObject)
		{

			if (m_bulletType == BulletType::Explosive)
			{
				auto spritePosition = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);

				m_explosionCirclePos = sf::Vector2f(spritePosition.x, spritePosition.y - m_explosionPositionOffset);
		
				m_currenExplosionAnimationSprite.setPosition(sf::Vector2f(spritePosition.x, spritePosition.y - m_explosionPositionOffset));

				int size = m_bulletExplosionAnimation.size();

				if (!m_isBulletExploding)
				{
					return;
				}
				else
				{
					if (m_endExplosionAnimation == false)
					{
						

						playExplosionAnimation(m_currenExplosionAnimationSprite);

						if (m_explosioTochTarget)
						{
							const auto& center = b2Vec2(spritePosition.x, spritePosition.y -m_explosionPositionOffset);

							auto damagedObjects =
								m_collider->performOverlapCircle(center, m_explosionAreaSize);


							for (auto* damagedObj : damagedObjects)
							{
								b2Body* body = damagedObj->GetBody();
								auto* collider = reinterpret_cast<ColliderBase*>(body->GetUserData().pointer);

								if(auto* capsule = dynamic_cast<CapsuleCollider*>(collider))
								{

									GameObject* object = capsule->m_obj;

									if (!object)
										continue;

									if (auto* creature = dynamic_cast<Creature*>(object))
									{
										if (creature->m_faction != this->m_faction)
										{
											if (m_hitCreatures.find(creature) != m_hitCreatures.end())
												continue;

											m_hitCreatures.insert(creature);

											creature->TakeDamage(m_damage);
										}
									}
								}

							}
						}
						
					}
					else
					{
						m_hitCreatures.clear();
						
						m_explosioTochTarget = false;
						m_isBulletExploding = false;
						m_currenExplosionIndex = 0;

						Weapon::releaseBullet(this);
					}
				}
			}
		
		}

		auto spritePosition = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);

		m_sprite.setPosition(spritePosition);
		


		if (m_bulletTimer.GetElapsed().asSeconds() >= m_bulletLifeLimit)
		{
			m_bulletTimer.Restart();

			Weapon::releaseBullet(this);
		}
	}

	void Bullet::setBulletPositionCenter(const sf::Vector2f& position, const sf::Vector2f& direction, const bool& facingRight)
	{

		if (auto* rectangleCollider = dynamic_cast<RectAngleCollider*>(m_collider))
		{

			// Collider position and rotation
			sf::Vector2f colliderPos = position;
			float rotationRadians = this->m_collider->getBody()->GetAngle();
			m_collider->getBody()->SetTransform(b2Vec2(colliderPos.x, colliderPos.y), rotationRadians);
			const auto& bodyPos = m_collider->getBody()->GetPosition();
			
			//Sprite position
			sf::Vector2f spritePos;
			spritePos = sf::Vector2f(bodyPos.x, bodyPos.y );
			m_sprite.setPosition(spritePos);

			// Sprite Rotation
			float angleDeg = (std::atan2(direction.y, direction.x) / M_PI) * 180.0f;
			if (direction.x < 0.0f)
			{
				angleDeg = -180.0f + angleDeg;
			}
			m_sprite.setRotation(angleDeg);
		}
		else if (auto* circleCollider = dynamic_cast<CircleCollider*>(m_collider))
		{

			// Collider position and rotation
			sf::Vector2f colliderPos = position;
			float rotationRadians = this->m_collider->getBody()->GetAngle();
			m_collider->getBody()->SetTransform(b2Vec2(colliderPos.x, colliderPos.y), rotationRadians);
			const auto& bodyPos = m_collider->getBody()->GetPosition();

			//Sprite position
			sf::Vector2f spritePos;
			spritePos = sf::Vector2f(bodyPos.x, bodyPos.y);
			m_sprite.setPosition(spritePos);

			// Sprite Rotation
			float angleDeg = (std::atan2(direction.y, direction.x) / M_PI) * 180.0f;
			if (direction.x < 0.0f)
			{
				angleDeg = -180.0f + angleDeg;
			}
			m_sprite.setRotation(angleDeg);
		}
		
	}

	void Bullet::invertCharacterMovingSpriteScale(int direction)
	{
		m_sprite.setScale(m_scale.x * (float)direction, m_scale.y);
	}
	void Bullet::launchBullet(const sf::Vector2f& direction, const float& speed)
	{

		b2Vec2 velocity(direction.x * speed, direction.y * speed);

		m_collider->getBody()->SetLinearVelocity(velocity);
	}
	void Bullet::launchBomb(const sf::Vector2f& direction, const float& speed)
	{
		std::cout << "Bomb Launched!" << std::endl;
	}
	void Bullet::bulletHandleEvents()
	{
		if (SceneManager::Get().m_isPaused)
		{
			m_bulletTimer.Freeze();
		}
		else if (!SceneManager::Get().m_isPaused)
		{
			m_bulletTimer.Resume();
		}
	}
	void Bullet::setOrignAtCenter()
	{
		auto bounds = m_sprite.getLocalBounds();
		m_sprite.setOrigin(bounds.width / 2.f,
			bounds.height / 2.f);
	}
	void Bullet::render(sf::RenderTarget& target)
	{

		GameObject::render(target);
		m_collider->drawColliderCenterBased(target);

		if (m_isBulletExploding)
		{

			if (m_currenExplosionAnimationSprite.getTexture() == nullptr)
			{
				std::cout << "NO TEXTURE\n";
			}

			target.draw(m_currenExplosionAnimationSprite);

			drawExplosionArea(m_explosionCirclePos, m_explosionAreaSize, target);
		}



	}
	void Bullet::buildExplosionAnimation()
	{

		if (m_bulletType != BulletType::Explosive)
		{
			return;
		}

	
		bool imageValid = false;
		do 
		{

			int imgIndex = m_bulletExplosionAnimation.size();
			int strImgIndex = imgIndex + 1;

			std::stringstream ss;
			ss << m_bulletExplosionPath;
			ss << "/";

			ss << "Explosion";
			ss << strImgIndex;
			ss << ".png";

			std::string path = ss.str();
			ss.clear();

			const auto* texture = ResourceManager::getInstance()->findOrFetchTexture(path);
			imageValid = texture != nullptr;

			if (imageValid)
			{
				m_bulletExplosionAnimation.push_back(*texture);
			}

		} while (imageValid);

	}
	void Bullet::playExplosionAnimation(sf::Sprite& sprite)
	{
		if (m_bulletExplosionAnimation.empty())
		{
			return;
		}

		if (m_currenExplosionIndex == 0)
		{
			if (m_isExpplosionAnimationTrasition)
			{
				m_isExpplosionAnimationTrasition = false;

				sf::Vector2u texSize = m_bulletExplosionAnimation[m_currenExplosionIndex].getSize();
				sprite.setTexture(m_bulletExplosionAnimation[m_currenExplosionIndex]);
				sprite.setTextureRect(sf::IntRect(0, 0, texSize.x, texSize.y));

				sprite.setOrigin(
					texSize.x / 2.f,
					texSize.y / 2.f
				);

			}

			if (m_explosionAnimationTimer.GetElapsed().asSeconds() >= m_explosionAnimationTimeLimit || getExplosionAnimationSwitch())
			{
				m_isExpplosionAnimationTrasition = true;

				bool increaseFrameIndex = true;
				if (m_currenExplosionIndex >= m_bulletExplosionAnimation.size() - 1)
				{
					increaseFrameIndex = false;
					if (m_repeatExplosionAnimation)
					{
						m_currenExplosionIndex = 0;
					}
					else
					{
						m_endExplosionAnimation = true;
					}
				}
				if (increaseFrameIndex)
				{
					m_currenExplosionIndex++;
				}

				m_explosionAnimationTimer.Restart();
			}
		}
		else if (m_currenExplosionIndex > 0)
		{
			if (m_isExpplosionAnimationTrasition)
			{
				m_isExpplosionAnimationTrasition = false;

				sf::Vector2u texSize = m_bulletExplosionAnimation[m_currenExplosionIndex].getSize();
				sprite.setTexture(m_bulletExplosionAnimation[m_currenExplosionIndex]);
				sprite.setTextureRect(sf::IntRect(0, 0, texSize.x, texSize.y));
			}

			if (m_explosionAnimationTimer.GetElapsed().asSeconds() >= m_explosionAnimationTimeLimit || getExplosionAnimationSwitch())
			{
				m_isExpplosionAnimationTrasition = true;

				bool increaseFrameIndex = true;
				if (m_currenExplosionIndex >= m_bulletExplosionAnimation.size() - 1)
				{
					increaseFrameIndex = false;
					if (m_repeatExplosionAnimation)
					{
						m_currenExplosionIndex = 0;
					}
					else
					{
						m_endExplosionAnimation = true;
					}
				}
				if (increaseFrameIndex)
				{
					m_currenExplosionIndex++;
				}

				m_explosionAnimationTimer.Restart();
			}
		}
	}
	void Bullet::OnSensorEnter(GameObject* obj)
	{
		if (isActive() == false) return;


		PhysicsLayer layer = static_cast<PhysicsLayer>(obj->m_collider->m_userDataName);

		if (layer == PhysicsLayer::Platforms)
		{
			if (m_bulletType == BulletType::Explosive)
			{
				m_isBulletExploding = true;

				m_explosioTochTarget = true;

				m_activeGameObject = false;
				m_activeRenderer = false;
				m_collider->getBody()->SetGravityScale(0.f);

				m_endExplosionAnimation = false;
				m_isExpplosionAnimationTrasition = true;
				m_currenExplosionIndex = 0;


				m_explosionAnimationTimer.Restart();

				if (m_collider)
				{
					if (auto* body = m_collider->getBody())
					{
						m_explosionCenter = m_collider->getBody()->GetPosition();
						body->SetAwake(false);

						body->SetGravityScale(0.0f);
					}
				}

			}
			else
			{
				Weapon::releaseBullet(this);
			}
		}
		else if (layer == PhysicsLayer::Creature)
		{
			if (obj->m_faction != this->m_faction)
			{
				if (auto* creature = dynamic_cast<Creature*>(obj))
				{
					if (m_bulletType == BulletType::Explosive)
					{
						if (creature->m_isDeath)
						{
							return;
						}
						else
						{
							creature->TakeDamage(m_damage);
						}

						m_isBulletExploding = true;

						m_activeGameObject = false;
						m_activeRenderer = false;
						m_collider->getBody()->SetGravityScale(0.f);

						m_endExplosionAnimation = false;
						m_isExpplosionAnimationTrasition = true;
						m_currenExplosionIndex = 0;


						m_explosionAnimationTimer.Restart();

						if (m_collider)
						{
							if (auto* body = m_collider->getBody())
							{
								body->SetAwake(false);

								body->SetGravityScale(0.0f);
							}
						}

					}
					else
					{
						if (creature->m_isDeath)
						{
							return;
						}
						else
						{
							creature->TakeDamage(m_damage);
							Weapon::releaseBullet(this);

						}
					}
				}

			}
		}
	}

	void Bullet::OnSensorExit(GameObject* obj)
	{
		if (isActive() == false) return;
	}

	void Bullet::resetForReuse()
	{
		if (m_collider)
		{
			if (auto* body = m_collider->getBody())
			{
				body->SetGravityScale(m_collider->m_gravityScale);
			}
		}
	}

	bool Bullet::getExplosionAnimationSwitch()
	{
		bool anim_switch = m_explosionAnimationSwitch;

		if (m_explosionAnimationSwitch)
		{
			m_explosionAnimationSwitch = false;
		}

		return anim_switch;
	}
}

