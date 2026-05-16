#pragma once

#include "GameObject.h"


namespace ratchet
{
	class Obstacle : public GameObject
	{
	public:
		Obstacle(ObstacleConfig& config);

		~Obstacle();

		float m_damage;
		float m_animationActiveTimePass;
		float m_colliderOffsetX;
		float m_colliderOffsetY;
		bool m_isAnimationPlaying;

		void update() override;
		void render(sf::RenderTarget& target) override;

		virtual void OnSensorEnter(GameObject* obj) override;
		virtual void OnSensorExit(GameObject* obj) override;

	private:
	
	};

}


