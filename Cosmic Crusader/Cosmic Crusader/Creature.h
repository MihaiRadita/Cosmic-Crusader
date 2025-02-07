#pragma once
#include "GameObject.h"
#include "CreatureConfig.h"


#include "animations/Animator.h"
#include "animations/AnimationIdle.h"
#include "animations/AnimationRun.h"
#include "animations/AnimationJump.h"
#include "animations/AnimationJumpRun.h"
#include "animations/Animator.h"
#include "WeaponManager.h"

namespace ratchet
{
	class Creature : public GameObject
	{
	public:


		//Character Features
		float m_movementSpeed;
		float m_fallingSpeed;
		float m_jumpImpulse;
		bool m_isMoving;

		//Character Animations
		std::map<ANIMATION_STATE, AnimationBase*> m_animationList;
		int m_characterAnimSwitch;
		ANIMATION_STATE m_characterAnimationState;
		std::vector<std::string> animationsTexturesPath;
		std::string creatureFallingTexturePath;
		Animator* m_characterAnimator;
		sf::Texture m_creatureFallingTexture;

		bool m_isFalling;

		//Constructors
		Creature(const CreatureConfig& config);

		//Destructors
		~Creature() override;

		//Update Function
		void update() override;
		void updateInput() override;
		void updateMovement() override;
		void updateRotation() override;
		void updatePhysics() override;
		void updateAnimations();
		void updateJump() override;
		void updateRunningJump() override;

		//Render functions

		//Sprite functions
		void invertCharacterMovingSpriteScale(int direction);
		bool isNoControlActive();

		//Input functions

		//Animation functions
		void switchAnimation();

		// Physics
		bool isGrounded() const { return m_isGround; };


		//Setters

		void addWeapon(Weapon::TYPE weaponType, std::optional<WeaponConfig> config);
		void setWeapon(int weaponIndex);

		 int m_equippedWeaponIndex = -1;


		 std::map<Weapon::TYPE, bool> m_usableWeaponTypeList; 
		 std::vector<std::pair<Weapon::TYPE, std::optional<WeaponConfig>>> m_weaponConfigList; 
		 std::vector<Weapon*> m_ownedWeaponList; 
		 std::vector<Weapon::TYPE> m_usableWeaponTypes;



		 WeaponAnimation::ANGLE m_currentCharacterAngle;
		 WeaponAnimation::STATE m_currentCharacterState;
		 Weapon::TYPE m_currentWeaponType;

	private:
		bool m_isGround;
	};
}


