#pragma once

enum PLAYER_ANIMATION_STATES{IDLE =0, MOVING_LEFT, MOVING_RIGHT, JUMP};

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;

	short animationState;
	float playerSpeed;

public:
	
	//Constructors
	Player();

	//Init functions
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
	void initIdleAnimation();
	void initPhysics();
	//Geters
	const sf::FloatRect getBounds() const;
	sf::Sprite GetPlayerSprite();
	const sf::Vector2f getPlayerPosition() const;
	sf::Vector2f getPlayerScale();

	//Modifiers
	void SetPosition(const float x, const float y);

	//Update functions
	void update();
	void updateMovement();
	void updateAnimations();
	void updatePhysics();

	//Render
	void render(sf::RenderTarget& target);
};

