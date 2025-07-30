#pragma once
#include "physics/Physics.h"
#include "physics/CircleCollider.h"
#include "physics/RectAngleCollider.h"
#include "CapsuleCollider.h"
#include "ColliderBase.h"
#include "ResourceManager.h"
#include "PrefabAssets.h"



namespace ratchet
{

	class GameObject
	{
	public:


		//States
		Faction m_faction;
		MovementType m_movementType;
		ColliderType m_colliderType;

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

		//Setters
		void SetPositionAndRotation(const sf::Vector2f& position, const float& rotationDegrees);

		virtual void invertCharacterMovingSpriteScale(int direction);

		//Physics
		sf::Vector2f m_colliderScaleMultipier;
		ColliderBase* m_collider = nullptr;


		static std::vector<GameObject*> s_gameObjects;
		static std::queue<GameObject*> s_gameObjectsToDestroy;
		static std::unordered_set<GameObject*> s_destroyQueuedSet;

		static GameObject* findGameObject(const b2Body* body);

		//Constructor
		GameObject();
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

		 static void addGameObjectoDestory(GameObject* object);

		 //Transforrms setters
		 virtual void setPosition(const sf::Vector2f position);
		 virtual void setRotation(const float angle);

		 //Destory functions
		 void DestroyGameObject();
		 void RemoveGameObjectFromList();
		 static void clearQueuedObjectsToDestroy();

		template<typename GameObjectChildType, typename GameObjectChildConfig>
		static GameObject* Instantiate(const GameObjectChildConfig gameObjectConfig, const sf::Vector2f& position, const float& rotationDegrees, bool& orientation);
			
		


		virtual void destroy();
	protected:
		struct Input
		{
			float x = 0;
			float y = 0;
			bool isJump = false;
			int weaponInputIndex = -1;
			bool m_isFiring = false;

			void resetMovementControls();
			
			void resetJumpControls();

			void resetControls();
			
			
		} m_input, m_previousInput;

#ifdef IS_RATCHET_DEBUG
		bool m_debugDraw = false;
#endif
	};

	template<typename GameObjectChildType, typename GameObjectChildConfig>
	ratchet::GameObject* ratchet::GameObject::Instantiate(const GameObjectChildConfig gameObjectConfig, const sf::Vector2f& position, const float& rotationDegrees, bool& orientation)
	{
		auto* newGameObject = new GameObjectChildType(gameObjectConfig);

		b2Vec2 colliderPosition = b2Vec2(position.x, position.y);
		float rotationRadians = rotationDegrees * M_PI / 180.f;

		if (newGameObject->m_collider)
		{
			newGameObject->m_collider->getBody()->SetTransform(colliderPosition, rotationRadians);
		}

	
		newGameObject->invertCharacterMovingSpriteScale(orientation ? 1 : -1);


		auto bodyPos = newGameObject->m_collider->getBody()->GetPosition();
		newGameObject->getSprite().setPosition(bodyPos.x, bodyPos.y);

	
		//newGameObject->getSprite().setRotation(newGameObject);

	
		ratchet::GameObject::s_gameObjects.emplace_back(newGameObject);
		return newGameObject;
	}


}

