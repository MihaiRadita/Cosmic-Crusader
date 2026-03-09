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
		ObjectType m_objectType;

		//Transforms
		sf::Vector2f m_position;
		float m_rotation;
		sf::Vector2f m_scale;
		
		int m_objectId;

		//Graphics
		std::string m_spritePath;
		std::string m_startSpritePath;
		sf::Sprite m_sprite;
		sf::Texture m_spriteTexture;

		bool m_activeGameObject;
		bool m_activeRenderer;
		

		//Getters
		sf::Sprite getSprite();
		sf::Vector2f getPosition();
		float getRotation();
		sf::Vector2f getScale();
		sf::FloatRect getBounds();
		sf::FloatRect getLocalBounds();
		ColliderBase* getCollider();
		bool m_markedForDestruction = false;
		
		//GameObject* m_target;

		//Setters
		void SetPositionAndRotation(const sf::Vector2f& position, const float& rotationDegrees);
		void SetActiveRenderer(bool active);
		void SetActiveObject(bool active);

		void setColliderToDestroy();

		virtual void PostCosntructFixup();

		virtual void Awake();
		virtual void Start();

		virtual void invertCharacterMovingSpriteScale(int direction);

		virtual void RestartObjectFeatures();

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

		//Save Functions
		virtual void serialise(nlohmann::json& jsonFile);
		virtual void resetSerialise(nlohmann::json& orginaljsonFile, nlohmann::json& jsonFile);

		//Getters
		const sf::FloatRect getBounds() const;

		//Render function
		virtual void render(sf::RenderTarget& target);

		 static GameObject* findGameObjectByBody(const b2Body* body);

		 static void addGameObjectoDestory(GameObject* object);

		 static void removeGameObjectToDestroy(GameObject* object);

		 virtual bool isActive() const;
		 virtual void setActive(bool active);

		 //Transforrms setters
		 virtual void setPosition(const sf::Vector2f position);
		 virtual void setRotation(const float angle);
		 virtual void setPositionRotationOrientation(
			 const sf::Vector2f position,
			 const float rotationDegrees,
			 const bool orientation);

		 //Destory functions
		 void DestroyGameObject();
		 void RemoveGameObjectFromList();
		 static void clearQueuedObjectsToDestroy();

		 void setDebugDraw(bool value);

		 bool getDebuDraw();

		template<typename GameObjectChildType, typename GameObjectChildConfig>
		static GameObject* Instantiate(
			const GameObjectChildConfig& gameObjectConfig, 
			const sf::Vector2f position = sf::Vector2f(0.0f, 0.0f),
			const float rotationDegrees = 0.0f, 
			const bool orientation = false
		);
			
		


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
	ratchet::GameObject* ratchet::GameObject::Instantiate(
		const GameObjectChildConfig& gameObjectConfig, 
		const sf::Vector2f position, 
		const float rotationDegrees, 
		const bool orientation
	)
	{
		auto* newGameObject = new GameObjectChildType(gameObjectConfig);
		newGameObject->setPositionRotationOrientation(position, rotationDegrees, orientation);
	
		ratchet::GameObject::s_gameObjects.emplace_back(newGameObject);
		return newGameObject;
	}
}

