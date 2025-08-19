// standard library
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <list>
#include <cmath>

// third party library
#include <../ThirdParty/fmod/core/inc/fmod.hpp> 
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

//core
#include "Core/Factory.h"
#include "Core/File.h"
#include "Core/Logger.h"
#include "Core/Random.h"
#include "Core/Singleton.h"
#include "Core/StringHelper.h"
#include "Core/Time.h"
#include "Core/Json.h"

//math
#include "Math/Math.h"
#include "Math/Transform.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

//framework
#include "FrameWork/Actor.h"
#include "FrameWork/Game.h"
#include "FrameWork/Scene.h"

//resources
#include "Resources/Resource.h"
#include "Resources/ResourceManager.h"