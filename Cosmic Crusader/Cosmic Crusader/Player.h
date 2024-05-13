#pragma once

#include "Animator.h"
#include "PlayerIdleAnimation.h"
#include "PlayerRunningAnimation.h"
#include "PlayerJumpAnimation.h"
#include "PlayerJumpRunningAnimation.h"
#include "RectAngleCollider.h"

enum PLAYER_ANIMATION_STATES{IDLE =0, MOVING_LEFT, MOVING_RIGHT, JUMP, JUMP_RUNNING};

class Player
{
private:

	//Player variables
	sf::Sprite playerSprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;
	sf::Event playerInputEvent;
	sf::Vector2f playerPosition;
	int playerAnimSwitch;
	sf::Vector2f playerSpriteScale;

	//Player Animation Instances
	Animator* playerAnimator;

	PlayerIdleAnimation* playerIdleAnimation;
	PlayerRunningAnimation* playerRunningAnimation;
	PlayerJumpAnimation* playerJumpAnimation;
	PlayerJumpRunningAnimation* playerJumpRunningAnimation;

	//Animations Destroy
	void DestroyPlayerAnimations();

	//Player Collider
	RectAngleCollider* playerCollider;

	//Physics Destroy
	void DestroyPlayerPhysics();

	// Variables
	short animationState;
	float moveSpeed;
	bool IsPLayerEvent;
	float gravity;
	bool isGround;
	bool isJumping;
	bool isMoving;
	float jumpForce;
	float yVelocity;
	bool isJumpStage;

	std::map<std::string, bool> controls{ {"left", false}, {"right", false}, {"jump", false}};
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
	sf::Sprite GetPlayerSprite();
	const sf::Vector2f getPlayerPosition() const;
	sf::Vector2f getPlayerScale();
	bool CheckEvent();
	
	//Setters
	void SetBoolEvent(bool isEv);

	void handleEvent(const sf::Event& event);

	void SetPlayerByColliderPos();

	//Modifiers
	void SetPosition(const float x, const float y);
	void resetControls();
	bool isNoControlActive();

	//Update functions
	void update();
	void updateAnimations();
	void updateMovement();
	void updatePhysics();
	void updateJump();
	void updateRunningJump();
	void setIsOnGround(bool isGround);
	void InvertPlayerMovingSpriteScale(int direction);
	void SwitchAnimation();
	bool IsJumping();

	//Render
	void render(sf::RenderTarget& target);

	//Destructor
	~Player();
};

