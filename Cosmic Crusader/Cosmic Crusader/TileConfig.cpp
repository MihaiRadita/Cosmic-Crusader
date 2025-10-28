#include "stdafx.h"
#include "TileConfig.h"

#include "game/Game.h"


namespace ratchet
{
	bool TileConfig::serialise(nlohmann::json& jsonFile)
	{
		return GameObjectConfig::serialise(jsonFile);
	}

	bool TileConfig::deserialise(const nlohmann::json& jsonFile)
	{
		GameObjectConfig::deserialise(jsonFile);

		float tileWidth = jsonFile["width"];
		float tileHeight = jsonFile["height"];

		scale = sf::Vector2f(1.0f, 1.0f) * Game::sc_tiledToGameScale;
		positionXOffset = 0.f;
		positionYOffset = -tileHeight * scale.y;

		float posX = jsonFile["x"].get<float>()* scale.x;
		float posY = jsonFile["y"].get<float>()* scale.y;

		posY += positionYOffset;

		position = sf::Vector2f(posX, posY);
		rotation = jsonFile["rotation"];
		startSpriteTexturePath = "";
		startSpriteTexturePathAddition = "";

		// Custom Properties
		m_colliderConfig = new RectAngleColliderConfig();
		for (const auto& jsonProperty : jsonFile["properties"])
		{
			const auto& propertyName = jsonProperty["name"];
			const auto& propertyValue = jsonProperty["value"];

			if (propertyName == "startSpriteTexturePath") startSpriteTexturePath = propertyValue.get<std::string>();

			if (propertyName == "Faction") m_Faction = static_cast<Faction>(propertyValue.get<int>());
			if (propertyName == "activeRenderer") m_activeRenderer = propertyValue.get<bool>();

			if (propertyName == "colliderLayer") m_colliderConfig->m_layer = static_cast<PhysicsLayer>(propertyValue.get<float>());
			if (propertyName == "colliderType") m_colliderConfig->m_bodyDef.type = static_cast<b2BodyType>(propertyValue.get<int>());
			if (propertyName == "colliderFixedRotation") m_colliderConfig->m_bodyDef.fixedRotation = propertyValue.get<bool>();
			if (propertyName == "colliderDensity") m_colliderConfig->m_fixtureDef.density = propertyValue.get<float>();
			if (propertyName == "colliderFriction") m_colliderConfig->m_fixtureDef.friction = propertyValue.get<float>();
			if (propertyName == "colliderRestitution") m_colliderConfig->m_fixtureDef.restitution = propertyValue.get<float>();
			if (propertyName == "colliderIsSensor") m_colliderConfig->m_fixtureDef.isSensor = propertyValue.get<bool>();
		}

		return true;
	}
}