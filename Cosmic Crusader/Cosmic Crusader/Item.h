#pragma once
#include "GameObject.h"

#include "game/Player.h"

#include "animations/Animator.h"


namespace ratchet
{
	class Item :  public GameObject
	{
	public:

		ItemType m_itemType;
		float m_itemContenntValue;
		bool m_isPickup = false;
		int m_itemRefferdId;
		float m_itemDisableTimePass;
		Timer m_itemDisabledTimer;
		bool m_isItemInteracting = false;
		bool m_isItemUsed = false;
		bool m_isItemAccessible = false;
		bool m_isAnimationPlaying;
		bool m_isOnItem = false;

		float m_springForce =0.0f;

		Animator* m_itemAnimator = nullptr;
		AnimationItem* m_itemAnimation;

		void handleItemtEvent(sf::Event& event);

		Creature* m_target;

		std::string m_spriteTextureOnPath = "";
		std::string m_spriteTextureOffPath = "";

		sf::Texture m_spriteTextureOn;
		sf::Texture m_spriteTextureOff;

		float m_animationTimeLimit;

		Item(ItemConfig& config);
		~Item();

		void update() override;
		void render(sf::RenderTarget& target) override;

		void updateItemsAnimations();

		void SetFriendTarget(Faction& faction);

		virtual void OnSensorEnter(GameObject* obj) override;
		virtual void OnSensorExit(GameObject* obj) override;

		virtual void OnCollisionEnter(GameObject* obj) override;
		virtual void OnCollisionExit(GameObject* obj)override;

		void serialise(nlohmann::json& jsonFile) override;


		void Start() override;

		void AddItemDestroyedID();


		void pickUpItem(Creature* creatureThatPickedUpTheItem);

	private:
	};
}

