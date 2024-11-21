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

//SFML
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"

//Box2D
#include "box2d/box2d.h"

//Json
#include "json.hpp"

//Windows
#include <Windows.h>

#define IS_RATCHET_DEBUG

#ifndef DBOUT
#define DBOUT( s )            \
{                             \
	std::wostringstream os_;    \
	os_ << s;                   \
	OutputDebugStringW(os_.str().c_str());  \
	OutputDebugStringW(L"\n");  \
}
#endif
