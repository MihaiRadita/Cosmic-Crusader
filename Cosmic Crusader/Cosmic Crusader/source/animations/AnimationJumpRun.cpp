#include "stdafx.h"
#include "AnimationJumpRun.h"
#include "ResourceManager.h"



namespace ratchet
{
	//Construcotrs
	AnimationJumpRun::AnimationJumpRun(std::string& texturePath, std::vector<Weapon::TYPE>& usableWeaponTypeList)
	{
		initVariables();

		for (const auto weaponType : usableWeaponTypeList)
		{
			if (weaponType != Weapon::TYPE::None)
			{
				for (int weaponAnimationAngleIndex = 0; weaponAnimationAngleIndex < (int)WeaponAnimation::ANGLE::Count; weaponAnimationAngleIndex++)
				{
					auto animationAngle = (WeaponAnimation::ANGLE)weaponAnimationAngleIndex;
					for (int weaponAnimationStateIndex = 0; weaponAnimationStateIndex < (int)WeaponAnimation::STATE::Count; weaponAnimationStateIndex++)
					{
						auto animationState = (WeaponAnimation::STATE)weaponAnimationStateIndex;

						int currentSize = m_weaponAnimationFramesMap[weaponType][animationAngle][animationState].size();

						m_weaponAnimationFramesMap[weaponType][animationAngle][animationState] =
							addAnimationFrames(
								texturePath,
								weaponType,
								WeaponAnimation::getWeaponAngleString(animationAngle),
								WeaponAnimation::getWeaponStateString(animationState)

							);
					}
				}
			}
			else
			{
				int currentSize = m_animationFrames.size();
				m_animationFrames = addAnimationFrames(texturePath, weaponType, "", "");
			}
		}
	}

	//Init functions
	void AnimationJumpRun::initVariables()
	{
		m_animTimeLimit = 0.02f;
		m_currentFrameIndex = 0;
		m_animTimeJumpLimit = 0.089f;
		m_jumpAnimFrameIndex = 1;
		m_isAnimTransition = true;

		m_initialTexture = false;
		m_animationTimer.restart();
		m_animationSwitch = true;
		m_currentJumpTimeLimit = m_animTimeLimit;
		m_repeatAnimation = false;

		m_endAnimation = false;
	}

	//Add animation frames images
	std::vector<sf::Texture> AnimationJumpRun::addAnimationFrames(std::string& texturePath, Weapon::TYPE weaponType, const char* aimingAngle, const char* state)
	{
		auto resultList = std::vector<sf::Texture>();
		bool imageValid = false;
		do
		{
			int imgIndex = resultList.size();
			int strImgIndex = imgIndex + 1;

			// Build string
			std::stringstream ss;
			ss << texturePath;
			ss << "JumpRunningTextures/";
			ss << Weapon::getWeaponTypeString(weaponType) << "/";
			if (strlen(aimingAngle) > 0)
			{
				ss << aimingAngle << "/";
			}
			if (strlen(state) > 0)
			{
				ss << state << "/";
			}
			ss << "JumpRunning";
			ss << strImgIndex;
			ss << ".png";
			std::string path = ss.str();
			ss.clear();

			// Load Texture
			const auto* texture = ResourceManager::getInstance()->findOrFetchTexture(path);
			imageValid = texture != nullptr;
			if (imageValid)
			{
				resultList.push_back(*texture);
			}

		} while (imageValid);

		return resultList;
	}

	//Play player animation frames
	void AnimationJumpRun::playAnimation(sf::Sprite& sprite, Weapon::TYPE& weaponUsed, WeaponAnimation::ANGLE& angle, WeaponAnimation::STATE& state)
	{
		if (!m_initialTexture)
		{
			m_currentFrameIndex++;
			m_initialTexture = true;
		}
		if (m_currentFrameIndex == 0)
		{
			if (m_isAnimTransition)
			{
				m_isAnimTransition = false;
				if (weaponUsed != Weapon::TYPE::None)
				{
					sf::Vector2u texSize = m_weaponAnimationFramesMap[weaponUsed][angle][state][m_currentFrameIndex].getSize();
					sprite.setTexture(m_weaponAnimationFramesMap[weaponUsed][angle][state][m_currentFrameIndex]);
					sprite.setTextureRect(sf::IntRect(0, 0, texSize.x, texSize.y));
				}
				else
				{
					sf::Vector2u texSize = m_animationFrames[m_currentFrameIndex].getSize();
					sprite.setTexture(m_animationFrames[m_currentFrameIndex]);
					sprite.setTextureRect(sf::IntRect(0, 0, texSize.x, texSize.y));
				}

#ifdef IS_RATCHET_DEBUG
				TRACE_CHANNEL("ANIMATION", "PLayer Idle image ", m_currentFrameIndex);
#endif

			}
			if (m_animationTimer.getElapsedTime().asSeconds() >= m_animTimeLimit || getAnimationSwitch())
			{
				m_isAnimTransition = true;

				bool increaseFrameIndex = true;
				if (m_currentFrameIndex >= getAnimSize(weaponUsed, angle, state) - 1)
				{
					increaseFrameIndex = false;
					if (m_repeatAnimation)
					{
						m_currentFrameIndex = 0;
					}
				}
				if (increaseFrameIndex)
				{
					m_currentFrameIndex++;
				}
				m_animationTimer.restart();
			}
		}
		else if (m_currentFrameIndex > 0)
		{
			if (m_isAnimTransition)
			{
				m_isAnimTransition = false;

				if (weaponUsed != Weapon::TYPE::None)
				{
					sf::Vector2u texSize = m_weaponAnimationFramesMap[weaponUsed][angle][state][m_currentFrameIndex].getSize();
					sprite.setTexture(m_weaponAnimationFramesMap[weaponUsed][angle][state][m_currentFrameIndex]);
					sprite.setTextureRect(sf::IntRect(0, 0, texSize.x, texSize.y));
				}
				else
				{
					sf::Vector2u texSize = m_animationFrames[m_currentFrameIndex].getSize();
					sprite.setTexture(m_animationFrames[m_currentFrameIndex]);
					sprite.setTextureRect(sf::IntRect(0, 0, texSize.x, texSize.y));
				}

#ifdef IS_RATCHET_DEBUG
				TRACE_CHANNEL("ANIMATION", "PLayer Idle image ", m_currentFrameIndex);
#endif
			}
			if (m_animationTimer.getElapsedTime().asSeconds() >= m_animTimeLimit || getAnimationSwitch())
			{
				m_isAnimTransition = true;

				bool increaseFrameIndex = true;

				if (m_currentFrameIndex >= getAnimSize(weaponUsed, angle, state) - 1)
				{
					increaseFrameIndex = false;
					if (m_repeatAnimation)
					{
						m_currentFrameIndex = 0;
					}
				}

				if (increaseFrameIndex)
				{
					m_currentFrameIndex++;
				}
				m_animationTimer.restart();
			}
		}
	}

	//Destroy functions
	AnimationJumpRun::~AnimationJumpRun()
	{
	}

	//Other functions
	void AnimationJumpRun::resetCurrentAnimIndex()
	{
		m_currentFrameIndex = 0;
	}

	void AnimationJumpRun::resetPlayerAnimTimer()
	{
		m_animationTimer.restart();
		m_animationSwitch = true;
	}

	void AnimationJumpRun::setAnimationSwitch(bool animSwitch)
	{
		m_animationSwitch = m_animationSwitch;
	}

	void AnimationJumpRun::invertAnimationFramesList(Weapon::TYPE& weaponused)
	{
		if (m_repeatAnimation)
		{
			if (weaponused != Weapon::TYPE::None)
			{
				for (auto& [weaponType, angleMap] : m_weaponAnimationFramesMap)
				{
					for (auto& [angle, stateMap] : angleMap)
					{
						for (auto& [state, textureVector] : stateMap)
						{
							std::reverse(textureVector.begin(), textureVector.end());
						}
					}
				}
			}
			else
			{
				std::reverse(m_animationFrames.begin(), m_animationFrames.end());
			}
		}
	}

	//Getters Functions
	int AnimationJumpRun::getAnimSize(Weapon::TYPE& type, WeaponAnimation::ANGLE& angle, WeaponAnimation::STATE& state)
	{
		if (type == Weapon::TYPE::None)
		{
			return m_animationFrames.size();
		}
		return m_weaponAnimationFramesMap[type][angle][state].size();
	}

	int AnimationJumpRun::getCurrentAnimIndex()
	{
		return m_currentFrameIndex;
	}

	bool AnimationJumpRun::getAnimationSwitch()
	{
		bool anim_switch = m_animationSwitch;

		if (m_animationSwitch)
		{
			m_animationSwitch = false;
		}

		return anim_switch;
	}

	bool AnimationJumpRun::isCurrentAnimationIndexValue()
	{
		if (m_currentFrameIndex == m_jumpAnimFrameIndex)
		{
			return  false;
#ifdef IS_RATCHET_DEBUG
			TRACE_CHANNEL("ANIMATION", "image number action ", m_jumpAnimFrameIndex, " happended!");
#endif
		}

		return true;
	}

}