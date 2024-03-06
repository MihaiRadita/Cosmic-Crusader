#pragma once

#include "Animator.h"
#include "PlayerIdleAnimation.h"
#include "PlayerRunningAnimation.h"

enum PLAYER_ANIMATION_STATES{IDLE =0, MOVING_LEFT, MOVING_RIGHT, JUMP};

class Player
{
private:

	//Player variables
	sf::Sprite sprite;
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

	//Animations Destroy
	void DestroyPlayerAnimations();

	short animationState;
	float moveSpeed;
	bool IsPLayerEvent;
	float gravity;
	bool isGround;
	bool isJumping;
	float jumpSpeed;
	float yVelocity;

	std::map<std::string, bool> controls{ {"left", false}, {"right", false}, {"jump", false}};
	//std::map<std::string, int> m{ {"CPU", 10}, {"GPU", 15}, {"RAM", 20} };
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

	//Modifiers
	void SetPosition(const float x, const float y);
	void resetControls();
	bool isAnyControlActive();

	//Update functions
	void update();
	void updateAnimations();
	void updateMovement();
	void updatePhysics();
	void updateJump();
	void setIsOnGround(bool isGround);
	void InvertPlayerMovingSpriteScale(int direction);

	//Render
	void render(sf::RenderTarget& target);

	//Destructor
	~Player();
};

