#include "stdafx.h"
#include "UISliderButtonConfig.h"

#include "SceneManager.h"

#include "EnumMask.h"

namespace ratchet
{
	UISliderButtonConfig::UISliderButtonConfig()
	{

	}
	UISliderButtonConfig::~UISliderButtonConfig()
	{

	}
	bool UISliderButtonConfig::serialise(nlohmann::json& jsonFile)
	{
		return false;
	}
	bool UISliderButtonConfig::deserialise(const nlohmann::json& jsonFile)
	{
		GameObjectConfig::deserialise(jsonFile);

		float tileWidth = jsonFile["width"];
		float tileHeight = jsonFile["height"];

		int id = jsonFile["id"].get<int>();

		scale = sf::Vector2f(1.0f, 1.0f) * SceneManager::sc_tiledToGameScale;
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

			if (propertyName == "buttonNameAction")
			{
				m_nameAction = static_cast<ButtonNameAction>(propertyValue.get<int>());
			}

			if (propertyName == "buttonNameState")
			{
				m_nameState = static_cast<ButtonNameState>(propertyValue.get<int>());
			}

			if (propertyName == "buttonParentNameState")
			{
				m_parentNameState = static_cast<ButtonNameState>(propertyValue.get<int>());
			}


			if (propertyName == "currentSliderValue")
			{
				m_currentSliderValue = propertyValue.get<float>();
			}


			if (propertyName == "minusButton")
			{
				int minusId = propertyValue.get<int>();

				nlohmann::json minusObj;

				if (SceneManager::Get().FindObjectById(minusId, minusObj, SceneManager::Get().GetLayerNameObjectByID(id)))
				{
					if(m_minusButtonConfig.deserialise(minusObj))
					{
						std::cout << "Slider Button SUCCESS!" << std::endl;
					}
				}
			}

			if (propertyName == "movementType")
			{
				m_movementType = static_cast<MovementType>(propertyValue.get<int>());
			}

			if (propertyName == "objectType")
			{
				m_objectType = static_cast<ObjectType>(propertyValue.get<int>());
			}

			if (propertyName == "plusButton")
			{
				int plusId = propertyValue.get<int>();

				nlohmann::json plusObj;
				if (SceneManager::Get().FindObjectById(plusId, plusObj,SceneManager::Get().GetLayerNameObjectByID(id)))
				{
					if (m_plusButtonConfig.deserialise(plusObj))
					{
						std::cout << "Slider Button SUCCESS!" << std::endl;
					}
				}
		
			}

			if (propertyName == "sliderMaxValue")
			{
				m_sliderMaxValue = propertyValue.get<float>();
			}

			if (propertyName == "sliderTitle")
			{
				int titleID = propertyValue.get<int>();

				nlohmann::json titleObj;

				if (SceneManager::Get().FindObjectById(titleID, titleObj, SceneManager::Get().GetLayerNameObjectByID(id)))
				{
					if (m_UITitleConfig.deserialise(titleObj))
					{
						std::cout << "Slider Text SUCCESS!" << std::endl;
					}
				}

			}

			if (propertyName == "sliderValueIncrease")
			{
				m_sliderValueIncreasse = propertyValue.get<float>();
			}

			if (propertyName == "sliderValueText")
			{
				int valueTextId = propertyValue.get<int>();

				nlohmann::json valueTextObj;

				if (SceneManager::Get().FindObjectById(valueTextId, valueTextObj, SceneManager::Get().GetLayerNameObjectByID(id)))
				{
					auto config = UITextConfig();
					if(config.deserialise(valueTextObj))
					{
						std::cout << "Slider Text SUCCESS!" << std::endl;
						m_UITextValueConfig = config;
					}
				}
			}
		}

		return true;
	}
}