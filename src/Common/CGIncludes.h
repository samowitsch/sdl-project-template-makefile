#ifdef _WIN32

#include <Box2D.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_net.h>

#include "../../includes/poly2tri/poly2tri.h"
#include "../../includes/clipper/clipper.hpp"

#elif _WIN64

#elif TARGET_OS_IPHONE

#include <Box2D/Box2D.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_ttf.h>

#include "../../includes/poly2tri/poly2tri.h"
#include "../../includes/clipper/clipper.hpp"

#elif TARGET_IPHONE_SIMULATOR

#include <Box2D/Box2D.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_ttf.h>

#include "../../includes/poly2tri/poly2tri.h"
#include "../../includes/clipper/clipper.hpp"

#elif TARGET_OS_MAC

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_net/SDL_net.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <Box2D/Box2D.h>

#include "../../includes/poly2tri/poly2tri.h"
#include "../../includes/clipper/clipper.hpp"

#elif __linux__

#include <box2d/box2d.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_ttf.h>

#include "../../includes/poly2tri/poly2tri.h"
#include "../../includes/clipper/clipper.hpp"

#endif