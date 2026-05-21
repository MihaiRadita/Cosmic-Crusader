#pragma once
#include "GameObject.h"
#include "Creature.h"
#include "game/Player.h"


namespace ratchet
{
	class Item :  public GameObject
	{
	public:

		ItemType m_itemType;
		float m_itemContenntValue;
		bool m_isPickup = false;
		int m_itemRefferdId;

		Item(ItemConfig& config);
		~Item();

		void update() override;
		void render(sf::RenderTarget& target) override;

		virtual void OnSensorEnter(GameObject* obj) override;
		virtual void OnSensorExit(GameObject* obj) override;

		void Start() override;

		void pickUpItem(Creature* creatureThatPickedUpTheItem);

	private:
	};
}

