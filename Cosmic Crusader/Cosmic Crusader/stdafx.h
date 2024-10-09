#include <cstdlib>
#include <ctime>
#include <iostream>
#include <time.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <sstream>
#include<fstream>
#include<math.h>

//Widnows

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

#ifdef IS_RATCHET_DEBUG
#undef IS_RATCHET_DEBUG
#endif