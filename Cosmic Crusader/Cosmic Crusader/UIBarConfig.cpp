#include "stdafx.h"
#include "UIBarConfig.h"

namespace ratchet
{
	UIBarConfig::UIBarConfig():GameObjectConfig()
	{
		m_barSizeX =0.0f;
		m_barSizeY =0.0f;
		m_barOffsetX =0.0f;
		m_barOffsetY =0.0f;
		m_rColor =0.0f;
		m_gColor =0.0f;
		m_bColor =0.0f;
		m_rBackColor =0.0f;
		m_gBackColor =0.0f;
		m_bBackColor =0.0f;

		m_spriteBarOffsetX = 0.0f;
		m_spriteBarOffsetY = 0.0f;

		m_barSpriteTexturePath = "";
	}
	UIBarConfig::~UIBarConfig()
	{

	}

	bool UIBarConfig::serialise(nlohmann::json& jsonFile)
	{
		return false;
	}
	bool UIBarConfig::deserialise(const nlohmann::json& jsonFile)
	{
		GameObjectConfig::deserialise(jsonFile);

		float tileWidth = jsonFile["width"];
		float tileHeight = jsonFile["height"];

		scale = sf::Vector2f(1.0f, 1.0f);

		positionXOffset = tileWidth / 2.0f;
		positionYOffset = tileHeight / 2.0f;


		m_objectID = jsonFile["id"];

		float posX = jsonFile["x"].get<float>();
		float posY = jsonFile["y"].get<float>();

		posX += positionXOffset;
		posY += positionYOffset;

		position = sf::Vector2f(posX, posY);
		rotation = jsonFile["rotation"];
		startSpriteTexturePath = "";
		startSpriteTexturePathAddition = "";


		m_colliderConfig = nullptr;

		if (jsonFile.contains("properties"))
		{
			for (const auto& jsonProperty : jsonFile["properties"])
			{
				const auto& propertyName = jsonProperty["name"];
				const auto& propertyValue = jsonProperty["value"];

				const auto& propertyType = jsonProperty["type"];


				if (propertyName == "Faction")
				{
					m_Faction = static_cast<Faction>(propertyValue.get<int>());
				}

				if (propertyName == "activeObject")
				{
					m_activeObject = propertyValue.get<bool>();
				}

				if (propertyName == "activeRenderer")
				{
					m_activeRenderer = propertyValue.get<bool>();
				}

				if (propertyName == "movementType")
				{
					m_movementType = static_cast<MovementType>(propertyValue.get<int>());
				}

				if (propertyName == "objectType")
				{
					m_objectType = static_cast<ObjectType>(propertyValue.get<int>());
				}

				if (propertyName == "barSizeX")
				{
					m_barSizeX = propertyValue.get<float>();
				}

				if (propertyName == "barSizeY")
				{
					m_barSizeY = propertyValue.get<float>();
				}

				if (propertyName == "barOffsetX")
				{
					m_barOffsetX = propertyValue.get<float>();
				}

				if (propertyName == "barOffsetY")
				{
					m_barOffsetY = propertyValue.get<float>();
				}

				if (propertyName == "spriteBarOffsetX")
				{
					m_spriteBarOffsetX = propertyValue.get<float>();
				}

				if (propertyName == "spriteBarOffsetY")
				{
					m_spriteBarOffsetY = propertyValue.get<float>();
				}

				if (propertyName == "rColor")
				{
					m_rColor = propertyValue.get<float>();
				}

				if (propertyName == "gColor")
				{
					m_gColor = propertyValue.get<float>();
				}

				if (propertyName == "bColor")
				{
					m_bColor = propertyValue.get<float>();
				}

				if (propertyName == "rBackColor")
				{
					m_rBackColor = propertyValue.get<float>();
				}

				if (propertyName == "gBackColor")
				{
					m_gBackColor = propertyValue.get<float>();
				}

				if (propertyName == "bBackColor")
				{
					m_bBackColor = propertyValue.get<float>();
				}

				if (propertyName == "barSpriteTexturePath")
				{
					m_barSpriteTexturePath = propertyValue.get<std::string>();
				}

				if (propertyName == "barTargetID")
				{
					m_hudBarTargetId = propertyValue.get<int>();
				}


			}
		}
		return true;
	}
}