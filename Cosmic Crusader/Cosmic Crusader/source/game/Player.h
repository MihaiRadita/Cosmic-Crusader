#pragma once

#include "animations/Animator.h"
#include "animations/AnimationIdle.h"
#include "animations/AnimationRun.h"
#include "animations/AnimationJump.h"
#include "animations/AnimationJumpRun.h"

#include "physics/RectAngleCollider.h"

namespace ratchet
{
	class Player
	{
	private:

		//Player variables
		sf::Sprite m_playerSprite;
		sf::Texture m_textureSheet;
		sf::Clock m_animationTimer;
		sf::Event m_playerInputEvent;
		int m_playerAnimSwitch;
		sf::Vector2f m_playerSpriteScale;
		float m_rotationAngle;

		//Player Animation Instances
		Animator* m_animator;

		AnimationIdle* m_animationIdle;
		AnimationRun* m_animationRun;
		AnimationJump* m_animationJump;
		AnimationJumpRun* m_animationJumpRun;

		//Animations Destroy
		void destroyPlayerAnimations();

		//Player Collider
		RectAngleCollider* m_collider;

		//Physics Destroy
		void destroyPlayerPhysics();

		// Variables
		short m_animationState;
		float m_moveSpeed;
		bool m_isPLayerEvent;
		float m_gravity;
		bool m_isGround;
		bool m_isJumping;
		bool m_isMoving;
		float m_jumpForce;
		float m_yVelocity;
		bool m_isJumpStage;

		UserData* m_userData;


		std::map<std::string, bool> m_controls{ {"left", false}, {"right", false}, {"jump", false} };
	public:

		//Constructors
		Player();

		//Init functions
		void initVariables();
		void initTexture();
		void initSprite();
		void initAnimations();
		void initPhysics();

		//Geters
		const sf::FloatRect getBounds() const;
		sf::Sprite getPlayerSprite();
		const sf::Vector2f getPlayerPosition() const;
		sf::Vector2f getPlayerScale();

		//Checks
		bool checkEvent();
#ifdef IS_RATCHET_DEBUG
		void printSpriteColliderPositionPlayer();
#endif

		//Setters
		void setBoolEvent(bool isEv);

		void handleEvent(const sf::Event& event);

		void setPlayerByColliderPos();

		//Modifiers
		void setPosition(const float x, const float y);
		void resetControls();
		bool isNoControlActive();

		//Update functions
		void update();
		void updateAnimations();
		void updateMovement();
		void updateRotation();
		void updatePhysics();
		void updateJump();
		void updateRunningJump();
		void setIsOnGround(bool isGround);
		void invertPlayerMovingSpriteScale(int direction);
		void switchAnimation();
		bool isJumping();

		//Render
		void render(sf::RenderTarget& target);

		//Destructor
		~Player();

	};
}
