#pragma once

#include "animations/AnimationBase.h"

namespace ratchet
{
	class AnimationJumpRun : public AnimationBase
	{
	public:
		void playAnimation(sf::Sprite& sprite) override;

		//Constructors
		AnimationJumpRun(std::string& texturePath);

		//Destructor
		~AnimationJumpRun();

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

		//Checking Conditions Functions
		bool getAnimationSwitch() override;
		bool isCurrentAnimationIndexValue() override;

	private:
		float m_animTimeJumpLimit;
		int m_jumpAnimFrameIndex;
		float m_currentJumpTimeLimit;
		// TODO: Foloseste ResourceManager asa cum am vorbit in loc de acest vector static.
		 std::vector<sf::Texture> s_animFrameImg;
	};
}
