#pragma once

#include <map>
#include "Windows.h"

#ifdef IS_RATCHET_DEBUG
#define TR_ENABLED IS_RATCHET_DEBUG
#endif

namespace hidden
{
	const std::map<const char*, bool> sc_traceChannelMap =
	{
		{ "ANIMATION",			false	},
		{ "ANIMATION_SPAM",		false	},
		{ "COLLISION",			false	},
		{ "GAME_OBJECT",		true	},
		{ "GAMEOBJECT_INIT",	false	},
		{ "MOUSE",				false	},
		{ "MOUSE_POSITION",		false	},
		{ "PHYSICS",			false	},
		{ "RENDERING",			false	},
		{ "RESOURCE_MANAGER",	false	},
		{ "WARNING",			true	},
		{ "WEAPON",				false	},
		{ "WEAPON_FIRE",		false	},
		{ "WEAPON_PICKUP",		false	},
		{"AI_TARGETING",			true} 
	};

	inline bool isTraceChannelEnabled(const char* channel)
	{
#ifdef TR_ENABLED
		if (!TR_ENABLED) return false;
#endif

		const auto it = sc_traceChannelMap.find(channel);
		if (it != sc_traceChannelMap.end())
		{
			return it->second;
		}

		return false;
	}

	inline void traceChannelLoop() // happens only once at the end of the traceChannelLoop
	{
		OutputDebugStringW(L"\n");
	}

	template <typename ARG_TYPE, typename... ARGS_TYPE>
	inline void traceChannelLoop(ARG_TYPE arg, ARGS_TYPE... args)
	{
		std::wostringstream os_;
		os_ << arg;

		OutputDebugStringW(os_.str().c_str());

		traceChannelLoop(args...);
	}

	template <typename ARG_TYPE, typename... ARGS_TYPE>
	inline void traceChannelStart(const char* channel, ARG_TYPE arg, ARGS_TYPE... args)
	{
		if (isTraceChannelEnabled(channel) == false) return;

		std::wostringstream os_;
		os_ << "[" << channel << "]: ";

		OutputDebugStringW(os_.str().c_str());

		traceChannelLoop(arg, args...);
	}
}

#define TRACE_CHANNEL( channel, ... ) hidden::traceChannelStart(channel, __VA_ARGS__)