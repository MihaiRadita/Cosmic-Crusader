#pragma once

namespace ratchet
{
	enum ANIMATION_STATE { 
		IDLE = 0, 
		MOVING_LEFT, 
		MOVING_RIGHT, 
		JUMP, 
		JUMP_RUNNING 
	};

	class AnimationBase
	{
	public:

		virtual void initVariables();

		//Other functions
		virtual void addAnimationFrames();
		virtual void destroyTextureFrames();

		virtual void playAnimation(sf::Sprite& sprite);
		virtual int getAnimSize();
		virtual int getCurrentAnimIndex();
		virtual sf::Clock getPlayerAnimTimer();
		virtual void resetCurrentAnimIndex();
		virtual void resetPlayerAnimTimer();
		virtual bool getAnimationSwitch();
		virtual void setAnimationSwitch(bool animSwitch);
		virtual bool isCurrentAnimationIndexValue();

	protected:
		float m_animTimeLimit;
		int m_currentFrameIndex;
		bool m_isAnimTransition;
		bool m_animationSwitch;
		sf::Clock m_animationTimer;
		bool m_initialTexture;
	};
}