#pragma once

#include "animations/AnimationBase.h"

namespace ratchet
{
	class AnimationIdle : public AnimationBase
	{
	public:
		void playAnimation(sf::Sprite& sprite) override;

		//Constructors
		AnimationIdle(std::string& texturePath);

		//Destructors
		~AnimationIdle();

		//Init functions
		void initVariables() override;

		//Other functions
		void addAnimationFrames(std::string& texturePath) override;
		void resetCurrentAnimIndex() override;
		void resetPlayerAnimTimer() override;
		void setAnimationSwitch(bool animSwitch) override;

		//Geters Functions	
		int getAnimSize() override;
		int getCurrentAnimIndex() override;
		bool getAnimationSwitch() override;

	private:
		std::vector<sf::Texture> m_animFrameImg;
	};
}