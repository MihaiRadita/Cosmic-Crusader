#pragma once

#include "animations/AnimationBase.h"

namespace ratchet
{
	class AnimationObstacle : public AnimationBase
	{
	public:
		AnimationObstacle(std::string& texturePath);

		~AnimationObstacle();

		void playAnimation(sf::Sprite& sprite) override;

		void initVariables() override;
		void resetPlayerAnimTimer() override;
		void resetCurrentAnimIndex() override;
		void resetAnimationFrame(sf::Sprite& sprite) override;

		int getAnimSize();
		int getCurrentAnimIndex() override;

		bool isAnimationReachedEnd();

		float getAnimTimeLimit() override;
		void SetAnimTimeLimit(float value) override;

		int m_frameIndexContinueAnimationFrom;

		std::vector<sf::Texture> addAnimationFrames(std::string& texturePath);

	private:
		std::vector<sf::Texture> m_animationFrames;

	};
}


