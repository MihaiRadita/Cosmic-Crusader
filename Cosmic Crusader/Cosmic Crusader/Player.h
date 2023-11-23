#pragma once

enum PLAYER_ANIMATION_STATES{IDLE =0, MOVING_LEFT, MOVING_RIGHT,MOVING_UP,MOVING_DOWN, JUMP};

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;
	sf::Event playerInputEvent;

	short animationState;
	float playerSpeed;
	bool IsPLayerEvent;

	std::map<std::string, bool> controls{ {"up", false },{"down", false}, {"left", false}, {"right", false} };
	//std::map<std::string, int> m{ {"CPU", 10}, {"GPU", 15}, {"RAM", 20} };
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
	bool CheckEvent();
	
	//Setters
	void SetBOOLEvent(bool isEv);

	void handleEvent(const sf::Event& event);

	//Modifiers
	void SetPosition(const float x, const float y);
	void resetControls();
	bool isAnyControlActive();

	//Update functions
	void update();
	void updateInput();
	void updateMovement();
	void updateAnimations();
	void updatePhysics();

	//Render
	void render(sf::RenderTarget& target);
};

