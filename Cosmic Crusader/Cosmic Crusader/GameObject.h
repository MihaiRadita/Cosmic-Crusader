#pragma once
#include "GameObjectConfig.h"
#include "physics/Physics.h"
#include "physics/RectAngleCollider.h"
#include "CapsuleCollider.h"
#include "ColliderBase.h"
#include "ResourceManager.h"
#include "Weapon.h"




namespace ratchet
{
	class GameObject
	{
	public:

		//States
		Faction m_faction;
		MovementType m_movementType;
		ColliderType m_colliderType;
		ColliderShapeType m_colliderShapeType;

		//Transforms
		sf::Vector2f m_position;
		float m_rotation;
		sf::Vector2f m_scale;
		
		//Graphics
		std::string m_spritePath;
		std::string m_startSpritePath;
		sf::Sprite m_sprite;
		sf::Texture m_spriteTexture;

		//Getters
		sf::Sprite getSprite();
		sf::Vector2f getPosition();
		float getRotation();
		sf::Vector2f getScale();
		sf::FloatRect getBounds();
		sf::FloatRect getLocalBounds();
		ColliderBase* getCollider();
		bool m_markedForDestruction = false;
		//Physics
		sf::Vector2f m_colliderScaleMultipier;
		ColliderBase* m_collider;


		static std::vector<GameObject*> s_gameObjects;

		static GameObject* findGameObject(const b2Body* body);

		//Constructor
		GameObject(const GameObjectConfig& config);

		//Destructor
		virtual ~GameObject();

		//Inits
		virtual void init();
		virtual void initGraphics();
		virtual void initPhyics();
		
		//Update functions
		virtual void update();
		virtual void updateInput();
		virtual void updatePhysics();
		virtual void updateRotation();
		virtual void updateMovement();
		virtual void updateJump();
		virtual void updateRunningJump();
		virtual void updateWeaponSelection();

		//Colision and Trigger interactions
		virtual void OnCollisionEnter(GameObject* obj);
		virtual void OnCollisionExit(GameObject* obj);
		virtual void OnSensorEnter(GameObject* obj);
		virtual void OnSensorExit(GameObject* obj);

		//Getters
		const sf::FloatRect getBounds() const;

		//Render function
		virtual void render(sf::RenderTarget& target);

		 static GameObject* findGameObjectByBody(const b2Body* body);

		 //Transforrms setters
		 virtual void setPosition(const sf::Vector2f position);
		 virtual void setRotation(const float angle);

		 void DestroyGameObject();
		 void RemoveGameObjectFromList();


		virtual void destroy();
	protected:
		struct Input
		{
			float x = 0;
			float y = 0;
			bool isJump = false;
			int weaponInputIndex = -1;

			void resetMovementControls();
			
			void resetJumpControls();

			void resetControls();
			
			
		} m_input;

#ifdef IS_RATCHET_DEBUG
		bool m_debugDraw = false;
#endif
	};

}

