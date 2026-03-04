#pragma once
#include "GameObject.h"



#include "animations/Animator.h"
#include "animations/AnimationIdle.h"
#include "animations/AnimationRun.h"
#include "animations/AnimationJump.h"
#include "animations/AnimationFall.h"
#include "animations/AnimationJumpRun.h"
#include "AnimationDeath.h"

#include "animations/Animator.h"
#include "WeaponManager.h"

#include "WindowManager.h"

#include "Timer.h"

#include "Bullet.h"

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
		int m_currentEquippedWeaponIndex;
		bool m_facingRight = true;
		bool m_previusFacingRight = false;
		bool m_isAnimationInverted = false;
		Timer m_fireCooldown;
		float m_fireRate; // Fires every m_fireRate seconds
		float m_recoilTime; // Recoil animation duration
		int m_lastFiredWeaponIndex = -1;
		bool m_mustSpawnBullet = false;
		bool m_isDeath = false;

		//target detect distance 
		float m_targetMaxDistanceDetectionX;
		float m_targetMaxDistanceDetectionY;

		bool m_isTargetDetected = false;
		bool m_isTagetBehindCharacter = false;

		//target lose distance
		float m_targetMaxDistanceLoseX;
		float m_targetMaxDistanceLoseY;

		float m_health = 0.0f;

		sf::Vector2f currentMousePositiion = sf::Vector2f(0.0f,0.0f);

		//Angles
		float m_baseAngle;
		float m_HalfBaseAngle;
		float m_DEG_TO_RAD;
		float m_tangentHalfBase;
		float m_tangentx3HalfBase; 

		float m_checkPointOffsetX;
		float m_checkPointOffsetY;

		//Charater boby areas points
		sf::Vector2f m_bodyShoulderPosition;
		float m_bodShoulderOffset;
		sf::CircleShape m_shape;


		//Character Animations
		std::vector<ANIMATION_STATE> m_animationStates;
		std::map<ANIMATION_STATE, AnimationBase*> m_animationList;
		int m_characterAnimSwitch;
		ANIMATION_STATE m_currentAnimationState;
		std::vector<std::string> animationsTexturesPath;
		std::string creatureFallingTexturePath;
		Animator* m_characterAnimator;
		sf::Texture m_creatureFallingTexture;

		bool m_isFallingWithoutJumping;

		//Constructors
		Creature(const CreatureConfig& config);

		//Destructors
		~Creature() override;

		//Update Function
		void update() override;
		void updateMovement() override;
		void updateRotation() override;
		void updatePhysics() override;
		void updateAnimations();
		void updateJump() override;
		void updateRunningJump() override;
		void updateWeaponSelection() override;
		void updateShooting();


		void serialise(nlohmann::json& jsonFile) override;
		void resetSerialise(nlohmann::json& originaljsonFile, nlohmann::json& jsonFile) override;

		//Render functions

		//Sprite functions
		void invertCharacterMovingSpriteScale(int direction) override;
		bool isNoControlActive();


		void PostCosntructFixup() override;

		void Start() override;

		//Input functions

		//Animation functions
		void switchAnimation();

		// Physics
		bool isGrounded() const { return m_isGround; };

		//Detections
		void detectTarget(GameObject* target);


		//Getters
		int getWeaponListSize();

		//Setters
		void addWeapon(Weapon::TYPE &weaponType, std::optional<WeaponConfig> &config);
		void setWeapon(int& weaponIndex);
		void setWeaponAccessible(Weapon::TYPE& weaponType, bool isAccessible);
		void setWeaponIndex(int index);

		//Checks
		bool isWeaponMatchCharacter(Weapon::TYPE& weaponType);
		bool isWeaponAccessible(Weapon::TYPE& weaponType);


		//Angles Functions
		virtual void computeAimAngleState();
		virtual void computeAimBulletRotation();

		//Shooting Points Function
		void computeShootingPoint();

		//Other functions
		void TakeDamage(float& damage);

		int m_equippedWeaponIndex = 0;


		//Shootings
		sf::Vector2f m_currentFirePoint;
		float m_currentFireRotationRadians;
		float m_currentFireRoationDegrees;
		sf::Vector2f m_currenFireDirectionNorm;
 
		std::vector<std::pair<Weapon::TYPE, std::optional<WeaponConfig>>> m_initialWeaponConfigList; 
		std::vector<Weapon*> m_ownedWeaponList; 
		std::vector <Weapon::TYPE> m_weaponTypeList;
		std::map<Weapon::TYPE, bool> m_usableWeaponTypeList;





		 WeaponAnimation::ANGLE m_currentCharacterAngle;
		 WeaponAnimation::STATE m_currentCharacterState;
		 std::vector<WeaponAnimation::ANGLE> m_characterAngles;

		 std::map<Weapon::TYPE, std::map< WeaponAnimation::ANGLE,sf::Vector2f>> m_shootingPointsOffsets;
		 std::map<Weapon::TYPE, sf::Vector2f> m_weaponsStartShootingPoint;

		 Weapon::TYPE m_currentWeaponType;

		 bool m_isRightNoWeapon;

		 float m_startShootingoffsetPointX;
		 float m_StartShootingOffsetPointY;

		 sf::CircleShape m_characterShootingPosition;
		 sf::CircleShape m_shootingPointDynamic;
		 sf::CircleShape m_shooitngPointCenter;

		 bool m_isGround;

	private:
	};
}


