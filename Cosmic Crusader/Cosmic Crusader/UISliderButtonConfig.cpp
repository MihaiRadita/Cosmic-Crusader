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



				auto* minusObj = SceneManager::Get().FindObjectById(minusId, SceneManager::Get().GetLayerNameObjectByID(id));

				if (minusObj)
				{
					if(m_minusButtonConfig.deserialise(*minusObj))
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

				auto* plusObj = SceneManager::Get().FindObjectById(plusId, SceneManager::Get().GetLayerNameObjectByID(id));
				if (plusObj)
				{
					if (m_plusButtonConfig.deserialise(*plusObj))
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

				auto* titleObj = SceneManager::Get().FindObjectById(titleID, SceneManager::Get().GetLayerNameObjectByID(id));

				if (titleObj)
				{
					if (m_UITitleConfig.deserialise(*titleObj))
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

				auto* valueTextObj = SceneManager::Get().FindObjectById(valueTextId, SceneManager::Get().GetLayerNameObjectByID(id));

				if (SceneManager::Get().FindObjectById(valueTextId, SceneManager::Get().GetLayerNameObjectByID(id)))
				{
					auto config = UITextConfig();
					if(config.deserialise(*valueTextObj))
					{
						std::cout << "Slider Text SUCCESS!" << std::endl;
						m_UITextValueConfig = config;
					}
				}
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

		}

		return true;
	}
}