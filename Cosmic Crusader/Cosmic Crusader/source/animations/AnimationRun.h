#pragma once

#include "animations/AnimationBase.h"

namespace ratchet
{
	class AnimationRun : public AnimationBase
	{
	public:
		void playAnimation(sf::Sprite& sprite) override;

		//Constructors
		AnimationRun(std::string& texturePath);

		//Destructor
		~AnimationRun();

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
		// TODO: Foloseste ResourceManager asa cum am vorbit in loc de acest vector static.
		 std::vector<sf::Texture> s_animFrameImg;
	};
}
