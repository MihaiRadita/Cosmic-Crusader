#include "stdafx.h"
#include "Creature.h"

namespace ratchet
{

	Creature::Creature(const CreatureConfig& config) : GameObject(config)
	{
		//Character Features
		m_movementSpeed = config.m_movingSpeed;
		m_fallingSpeed = config.m_fallingSpeed;
		m_jumpingSpeed = config.m_jumpingSpeed;

		m_characterAnimator = nullptr;
		m_spritePath = config.spriteTexturePath;

		if (m_faction == Faction::PLAYER)
		{
			m_characterAnimationState = IDLE;
			m_characterAnimator = new Animator();
			m_animationList.emplace(ANIMATION_STATE::IDLE, new AnimationIdle(m_spritePath));
			m_animationList.emplace(ANIMATION_STATE::JUMP, new AnimationJump(m_spritePath));
			m_animationList.emplace(ANIMATION_STATE::MOVING, new AnimationRun(m_spritePath));
			m_animationList.emplace(ANIMATION_STATE::JUMP_RUNNING, new AnimationJumpRun(m_spritePath));

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
	}

	void Creature::updateInput()
	{

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
		m_characterAnimator->play(m_characterAnimator->getAbstractAnimation(), m_sprite);
	}
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
		if (m_Input.x != 0 || m_Input.y != 0 || m_Input.isJump == true)
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
}

