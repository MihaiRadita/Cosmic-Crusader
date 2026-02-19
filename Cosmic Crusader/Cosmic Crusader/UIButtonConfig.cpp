#include "stdafx.h"
#include "UIButtonConfig.h"

#include "SceneManager.h"

#include "EnumMask.h"

namespace ratchet
{
	UIButtonConfig::UIButtonConfig() : GameObjectConfig()
	{
		m_uiButtonOffsetX = 0.0f;
		m_uiButtonOffsetY = 0.0f;
	}
	UIButtonConfig::~UIButtonConfig()
	{

	}
	bool UIButtonConfig::serialise(nlohmann::json& jsonFile)
	{
		return GameObjectConfig::serialise(jsonFile);
	}
	bool UIButtonConfig::deserialise(const nlohmann::json& jsonFile)
	{
		GameObjectConfig::deserialise(jsonFile);

		float tileWidth = jsonFile["width"];
		float tileHeight = jsonFile["height"];

		scale = sf::Vector2f(1.0f, 1.0f);
		positionXOffset = 0.f;
		positionYOffset = tileHeight;

		float posX = jsonFile["x"].get<float>();
		float posY = jsonFile["y"].get<float>();

		posY -= positionYOffset;

		position = sf::Vector2f(posX, posY);
		rotation = jsonFile["rotation"];
		startSpriteTexturePath = "";
		startSpriteTexturePathAddition = "";

		m_colliderConfig = nullptr;


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

			if (propertyName == "startSpriteTexturePath")
			{
				startSpriteTexturePath = propertyValue.get<std::string>();
			}

			if (propertyName == "buttonNameState")
			{
				m_nameState = static_cast<ButtonNameState>(propertyValue.get<int>());
			}

			if (propertyName == "buttonParentNameState")
			{
				m_parentNameState = static_cast<ButtonNameState>(propertyValue.get<int>());
			}

			if (propertyName == "buttonBackSection")
			{
				m_BackNameSection = static_cast<ButtonNameSection>(propertyValue.get<int>());
			}

			if (propertyName == "buttonNextSection")
			{
				m_NextNameSection = static_cast<ButtonNameSection>(propertyValue.get<int>());
			}

			if (propertyName == "buttonSection")
			{
				m_nameSection = static_cast<ButtonNameSection>(propertyValue.get<int>());
			}

			if (propertyName == "buttonUIXOffset")
			{
				m_uiButtonOffsetX = propertyValue.get<float>();
			}

			if (propertyName == "buttonUIYOffset")
			{
				m_uiButtonOffsetY = propertyValue.get<float>();
			}


			if (propertyName == "buttonNameAction")
			{
				m_nameAction = static_cast<ButtonNameAction>(propertyValue.get<int>());
			}
		}

		return true;
	}
}