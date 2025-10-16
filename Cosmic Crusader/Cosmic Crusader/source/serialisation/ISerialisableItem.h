#pragma once

namespace ratchet
{
	struct ISerialisableItem
	{
		virtual bool serialise(nlohmann::json& jsonFile) = 0;
		virtual bool deserialise(const nlohmann::json& jsonFile) = 0;
	};
}