#pragma once

#include "GameObject.h"

#include "PrefabAssets.h"

namespace ratchet
{
	class ActionTrigger : public GameObject
	{
	public:
		ActionTrigger(const ActionTriggerConfig& config);
		~ActionTrigger();


		ActionTriggerName m_actionTriggerName;

		bool m_isActionTriggerInteracting = false;

		float m_triggerShapeSizeX;
		float m_triggerShapeSizeY;

		void update() override;
		void render(sf::RenderTarget& target) override;

		void OnCollisionEnter(GameObject* obj) override;
		void OnCollisionExit(GameObject* obj) override;

		virtual void OnSensorEnter(GameObject* obj) override;
		virtual void OnSensorExit(GameObject* obj) override;

		void SetTarget();

		sf::RectangleShape m_actionTriggerShape;

	private:
	};
}


