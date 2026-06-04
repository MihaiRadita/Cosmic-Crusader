#pragma once

#include "GameObjectConfig.h"

namespace ratchet
{
	struct UIBarConfig : public GameObjectConfig
	{



		UIBarConfig();
		~UIBarConfig();

		virtual bool serialise(nlohmann::json& jsonFile) override;
		virtual bool deserialise(const nlohmann::json& jsonFile) override;

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

		int m_hudBarTargetId;


		std::string m_barSpriteTexturePath;

	};

}

