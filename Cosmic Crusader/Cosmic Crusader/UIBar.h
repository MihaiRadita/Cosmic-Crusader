#pragma once
#include "GameObject.h"

#include "PrefabAssets.h"


namespace ratchet
{
	class UIBar : public GameObject
	{
	public:

		UIBar(const UIBarConfig& config);

		~UIBar();

		void update() override;
		void render(sf::RenderTarget& target) override;

		float m_barSizeX;
		float m_barSizeY;

		float m_barOffsetX;
		float m_barOffsetY;

		float m_rColor;
		float m_gColor;
		float m_bColor;

		float m_rBackColor;
		float m_gBackColor;
		float m_bBackColor;

		float m_spriteBarOffsetX;
		float m_spriteBarOffsetY;

		std::string m_barSpriteTexturePath;
		sf::Texture m_barSpriteTexture;

		sf::RectangleShape m_hudBar;
		sf::RectangleShape m_hudBackBar;
		sf::Sprite m_hudBarSprite;

		int m_hudBarTargetId;


		void Start() override;

	private:
	};

}

