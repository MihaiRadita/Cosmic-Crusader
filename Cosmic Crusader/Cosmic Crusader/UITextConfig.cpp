#include "stdafx.h"
#include "UITextConfig.h"

#include "SceneManager.h"

#include "EnumMask.h"

namespace ratchet
{
	UITextConfig::UITextConfig()
	{

	}

	UITextConfig::~UITextConfig()
	{
	}
	bool UITextConfig::serialise(nlohmann::json& jsonFile)
	{
		return false;
	}
	bool UITextConfig::deserialise(const nlohmann::json& jsonFile)
	{
		GameObjectConfig::deserialise(jsonFile);

		float tileWidth = jsonFile["width"];
		float tileHeight = jsonFile["height"];

		scale = sf::Vector2f(1.0f, 1.0f) * SceneManager::sc_tiledToGameScale;
		float positionXOffsetUNit = tileWidth / m_XUnit;
		float positionYOffsetUnit = tileHeight / m_YUnit;
		positionXOffset = tileWidth / 2.0f;
		positionYOffset = tileHeight / 2.0f;


		float posX = jsonFile["x"].get<float>();
		float posY = jsonFile["y"].get<float>();

		posX += positionXOffset;
		posY += positionYOffset;

		position = sf::Vector2f(posX, posY);
		rotation = jsonFile["rotation"];
		startSpriteTexturePath = "";
		startSpriteTexturePathAddition = "";

		m_TextType = UITextType::None;
		m_textSize = 16.f;
		m_textColor = sf::Color::White;
		m_TextValue.clear();

		m_colliderConfig = nullptr;

		if (jsonFile.contains("text"))
		{
			const auto& textJson = jsonFile["text"];

			if (textJson.contains("text"))
			{
				m_TextValue = textJson["text"].get<std::string>();
			}

			if (textJson.contains("pixelsize"))
			{
				m_textSize = textJson["pixelsize"].get<float>();
			}

			if (textJson.contains("color"))
			{
				std::string colorStr = textJson["color"].get<std::string>();
				unsigned int rgba = std::stoul(colorStr.substr(1), nullptr, 16);

				sf::Uint8 a = (rgba >> 24) & 0xFF;
				sf::Uint8 r = (rgba >> 16) & 0xFF;
				sf::Uint8 g = (rgba >> 8) & 0xFF;
				sf::Uint8 b = rgba & 0xFF;

				m_textColor = sf::Color(r, g, b);
			}
			else
			{
				m_textColor = sf::Color::White;
			}
		}

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

				if (propertyName == "textFontPath")
				{
					m_textFontPath = propertyValue.get<std::string>();
				}

				if (propertyName == "textType")
				{
					m_TextType = static_cast<UITextType>(propertyValue.get<int>());
				}

				if (propertyName == "textValue")
				{
					m_TextValue = propertyValue.get<std::string>();
				}
			}

		}

		return true;
	}
}

