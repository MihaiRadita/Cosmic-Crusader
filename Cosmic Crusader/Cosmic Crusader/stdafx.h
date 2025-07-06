#include <algorithm>
#include <corecrt_math_defines.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <optional>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>
#include <variant>
#include<queue>

//Math C++
#define _USE_MATH_DEFINES 
#include <cmath>

//SFML
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window/Mouse.hpp"

//Box2D
#include "box2d/box2d.h"

//Json
#include "json.hpp"

//Windows
#include <Windows.h>


#ifndef TRACE_CHANNEL

#define TR_ENABLED IS_RATCHET_DEBUG

#define TR_RENDERING		TR_ENABLED && false
#define TR_COLLISION		TR_ENABLED && false
#define TR_MOUSE			TR_ENABLED && false
#define TR_GAMEOBJECT_INIT	TR_ENABLED && false
#define TR_ANIMATION		TR_ENABLED && false
#define TR_WEAPON			TR_ENABLED && false
#define TR_WEAPON_FIRE		TR_ENABLED && true
#define TR_RESOURCE_MANAGER TR_ENABLED && false
#define TR_PHYSICS			TR_ENABLED && false
#define TR_WEAPON_PICKUP	TR_ENABLED && false
#define TR_ANIMATION_SPAM   TR_ENABLED && false

#define TRACE_CHANNEL( show, s )            \
{                             \
	if(show)					\
	{								\
		std::wostringstream os_;    \
		os_ << s;                   \
		OutputDebugStringW(os_.str().c_str());  \
		OutputDebugStringW(L"\n");  \
	}					\
}
#endif
