#pragma once

#include "Creature.h"
#include "Timer.h"
#include "animations/Animator.h"

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

		int m_frameIndexContinueAnimationFrom;

		Animator* m_obstacleAnimator = nullptr;

		AnimationObstacle* m_obstacleAnimation;

		void update() override;
		void render(sf::RenderTarget& target) override;

		virtual void OnSensorEnter(GameObject* obj) override;
		virtual void OnSensorExit(GameObject* obj) override;

		void updateObstacleAnimations();

		void Start() override;

		Timer m_animationPlayInterval;

		Creature* m_target =nullptr;

		void SetTarget(Faction& faction);

		void updateDamage();

	private:
	
	};

}


