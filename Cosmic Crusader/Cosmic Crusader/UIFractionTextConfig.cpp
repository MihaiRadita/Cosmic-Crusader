#include "stdafx.h"
#include "UIFractionTextConfig.h"

#include "SceneManager.h"

namespace ratchet
{
	UIFractionTextConfig::UIFractionTextConfig()
	{
		m_currentSliderValue = 0.0f;
		m_sliderValueIncreasse = 0.0f;
		m_sliderMaxValue = 0.0f;
	}

	UIFractionTextConfig::~UIFractionTextConfig()
	{

	}
	bool UIFractionTextConfig::serialise(nlohmann::json& jsonFile)
	{
		return false;
	}
	bool UIFractionTextConfig::deserialise(const nlohmann::json& jsonFile)
	{
		GameObjectConfig::deserialise(jsonFile);

		float tileWidth = jsonFile["width"];
		float tileHeight = jsonFile["height"];

		int id = jsonFile["id"].get<int>();

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

		m_objectID = jsonFile["id"];

		m_colliderConfig = nullptr;


		for (const auto& jsonProperty : jsonFile["properties"])
		{
			const auto& propertyName = jsonProperty["name"].get<std::string>();
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

			if (propertyName == "currentValue")
			{
				int currentValueID = propertyValue.get<int>();

				auto* currentValueObj = SceneManager::Get().FindObjectById(currentValueID, SceneManager::Get().GetLayerNameObjectByID(id));

				if (currentValueObj)
				{
					if (m_currentValueConfig.deserialise(*currentValueObj))
					{
						std::cout << "Slider Text SUCCESS!" << std::endl;
					}
				}

			}

			if (propertyName == "maxValue")
			{
				int maxID = propertyValue.get<int>();

				auto* maxObj = SceneManager::Get().FindObjectById(maxID, SceneManager::Get().GetLayerNameObjectByID(id));

				if (maxObj)
				{
					if (m_maxValueConfig.deserialise(*maxObj))
					{
						std::cout << "Slider Text SUCCESS!" << std::endl;
					}
				}

			}

			if (propertyName == "fractionSeparator")
			{
				int fractionSeparatorID = propertyValue.get<int>();

				auto* fractionSeparatorObj = SceneManager::Get().FindObjectById(fractionSeparatorID, SceneManager::Get().GetLayerNameObjectByID(id));

				if (fractionSeparatorObj)
				{
					if (m_fractionSeparator.deserialise(*fractionSeparatorObj))
					{
						std::cout << "Slider Text SUCCESS!" << std::endl;
					}
				}

			}


		}
		return true;
	}
}