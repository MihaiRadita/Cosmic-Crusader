#include <cstdlib>
#include <ctime>
#include <iostream>
#include <time.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <math.h>
#include <corecrt_math_defines.h>

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

#undef IS_RATCHET_DEBUG

#ifndef DBOUT
#define DBOUT( s )            \
{                             \
	std::wostringstream os_;    \
	os_ << s;                   \
	OutputDebugStringW(os_.str().c_str());  \
	OutputDebugStringW(L"\n");  \
}
#endif
