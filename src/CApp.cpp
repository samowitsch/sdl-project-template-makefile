// ============================================================================
// [Include Section]
// ============================================================================
#include "Common/CGGlobals.h"

#include "CApp.h"
#include "CppCangaja/CGSprite.h"

// ============================================================================
// [Defines & Constants]
// ============================================================================
#define APPTITLE "SDL2 Template Program"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// image
SDL_Texture *bitmapTex = NULL;
SDL_Surface *bitmapSurface = NULL;

// sound
Mix_Music *music = NULL;

// ttf font
SDL_Color fontColor = {0, 0, 255, 255};
SDL_Rect fontRect = {20, 20, 400, 100};
SDL_Texture *fontImage;

// mouse position
int pointerX = 50;
int pointerY = 50;

CGSprite sprite = CGSprite(50, 50);

CApp::CApp() : running(false)
{
}

CApp::~CApp()
{
    OnCleanup();
}

int CApp::OnInit()
{    
    b2Vec2 vec;
    vec.IsValid();

    b2World world = b2World(vec);
    world.GetGravity();
    world.Dump();
    SDL_Log("b2world gravity: %f, %f\n", world.GetGravity().x, world.GetGravity().y);

    // Initialize the SDL library.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("SDL_Init() failed: %s\n", SDL_GetError());
        return APP_FAILED;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_SetHint(SDL_HINT_ORIENTATIONS, "LandscapeLeft LandscapeRight");

    //Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        SDL_Log("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }

    basePath = SDL_GetBasePath();
    SDL_Log("basePath: %s\n", basePath);

    // create the window
    window = SDL_CreateWindow(APPTITLE,
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    if (window != NULL)
    {
        // create renderer
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);

        // image loading example
        //bitmapSurface = SDL_LoadBMP("Pics/example.bmp");      // load bmp over SDL
        bitmapSurface = IMG_Load("Pics/example.png"); // load png over SDL_image
        bitmapTex = SDL_CreateTextureFromSurface(renderer, bitmapSurface);
        SDL_FreeSurface(bitmapSurface);

        sprite.loadTexture("Pics/mario.png");

        // music loading example
        music = Mix_LoadMUS("Sfx/beat.wav");
        Mix_PlayMusic(music, -1);
    }

    /* start SDL_ttf */
    if (TTF_Init() == -1)
    {
        SDL_Log("TTF_Init: %s\n", TTF_GetError());
    }

    fontImage = RenderText("TTF fonts are cool!", "Fonts/FreeSerifBold.ttf", fontColor, 32, renderer);

    // Success
    return APP_OK;
}

void CApp::OnCleanup()
{
    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window != NULL)
    {
        Mix_FreeMusic(music);
        music = NULL;
        SDL_DestroyWindow(window);
    }

    SDL_free(basePath);
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

int CApp::OnExecute()
{
    SDL_Log("Before preprocessor    OnExecute => __IPHONEOS__ => HandleAppEvents?");
#if __IPHONEOS__
    SDL_Log("OnExecute => __IPHONEOS__ => HandleAppEvents?");
    //iOS test
    //SDL_SetEventFilter(HandleAppEvents, NULL);
#endif

    // Initialize application.
    int state = OnInit();
    if (state != APP_OK)
    {
        return state;
    }

    // Enter the SDL event loop.
    SDL_Event event;

    running = true;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            OnEvent(&event);
        }

        OnUpdate();
        OnRender();
    }

    return state;
}

void CApp::OnEvent(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_MOUSEMOTION:
        //sprite.position->x = event->motion.x;
        //sprite.position->y = event->motion.y;
        break;
    case SDL_QUIT:
        running = false;
        break;

    case SDL_KEYDOWN:
        if (event->key.keysym.sym == SDLK_ESCAPE)
        {
            running = false;
        }
        if (event->key.keysym.sym == SDLK_LEFT)
        {
            sprite.position->x -= 10;
        }
        if (event->key.keysym.sym == SDLK_RIGHT)
        {
            sprite.position->x += 10;
        }
        if (event->key.keysym.sym == SDLK_UP)
        {
            sprite.position->y -= 10;
        }
        if (event->key.keysym.sym == SDLK_DOWN)
        {
            sprite.position->y += 10;
        }
    default:
        break;
    }
}

void CApp::OnUpdate()
{
    // Update your game logic here
    sprite.Update();
}

void CApp::OnRender()
{
    SDL_RenderClear(renderer);

    // Do your drawing here
    SDL_RenderCopy(renderer, bitmapTex, NULL, NULL);
    sprite.Draw();
    RenderTexture(fontImage, renderer, 100, 200);

    SDL_RenderPresent(renderer);
}

/**
 * Render the message we want to display to a texture for drawing
 * @param message The message we want to display
 * @param fontFile The font we want to use to render the text
 * @param color The color we want the text to be
 * @param fontSize The size we want the font to be
 * @param renderer The renderer to load the texture in
 * @return An SDL_Texture containing the rendered message, or nullptr if something went wrong
 */
SDL_Texture *CApp::RenderText(const std::string &message, const std::string &fontFile,
                              SDL_Color &color, int fontSize, SDL_Renderer *renderer)
{
    //Open the font
    TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (font == nullptr)
    {
        return nullptr;
    }
    //We need to first render to a surface as that's what TTF_RenderText
    //returns, then load that surface into a texture
    SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
    if (surf == nullptr)
    {
        TTF_CloseFont(font);
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
    if (texture == nullptr)
    {
    }
    //Clean up the surface and font
    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
    return texture;
}

/**
 * Draw an SDL_Texture to an SDL_Renderer at some destination rect
 * taking a clip of the texture if desired
 * @param tex The source texture we want to draw
 * @param ren The renderer we want to draw to
 * @param dst The destination rectangle to render the texture to
 * @param clip The sub-section of the texture to draw (clipping rect)
 *		default of nullptr draws the entire texture
 */
void CApp::RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip)
{
    SDL_RenderCopy(ren, tex, clip, &dst);
}

/**
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
 * the texture's width and height and taking a clip of the texture if desired
 * If a clip is passed, the clip's width and height will be used instead of
 *	the texture's
 * @param tex The source texture we want to draw
 * @param ren The renderer we want to draw to
 * @param x The x coordinate to draw to
 * @param y The y coordinate to draw to
 * @param clip The sub-section of the texture to draw (clipping rect)
 *		default of nullptr draws the entire texture
 */
void CApp::RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    if (clip != nullptr)
    {
        dst.w = clip->w;
        dst.h = clip->h;
    }
    else
    {
        SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    }
    RenderTexture(tex, ren, dst, clip);
}

/**
 *
 * @param userdata
 * @param event
 * @return
 */
int CApp::HandleAppEvents(void *userdata, SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_APP_TERMINATING:
        /* Terminate the app.
               Shut everything down before returning from this function.
             */
        SDL_Log("SDL_APP_TERMINATING");
        return 0;
    case SDL_APP_LOWMEMORY:
        /* You will get this when your app is paused and iOS wants more memory.
               Release as much memory as possible.
             */
        SDL_Log("SDL_APP_LOWMEMORY");
        return 0;
    case SDL_APP_WILLENTERBACKGROUND:
        /* Prepare your app to go into the background.  Stop loops, etc.
               This gets called when the user hits the home button, or gets a call.
             */
        SDL_Log("SDL_APP_WILLENTERBACKGROUND");
        return 0;
    case SDL_APP_DIDENTERBACKGROUND:
        /* This will get called if the user accepted whatever sent your app to the background.
               If the user got a phone call and canceled it, you'll instead get an SDL_APP_DIDENTERFOREGROUND event and restart your loops.
               When you get this, you have 5 seconds to save all your state or the app will be terminated.
               Your app is NOT active at this point.
             */
        SDL_Log("SDL_APP_DIDENTERBACKGROUND");
        return 0;
    case SDL_APP_WILLENTERFOREGROUND:
        /* This call happens when your app is coming back to the foreground.
               Restore all your state here.
             */
        SDL_Log("SDL_APP_WILLENTERFOREGROUND");
        return 0;
    case SDL_APP_DIDENTERFOREGROUND:
        /* Restart your loops here.
               Your app is interactive and getting CPU again.
             */
        SDL_Log("SDL_APP_DIDENTERFOREGROUND");
        return 0;
    default:
        /* No special processing, add it to the event queue */
        return 1;
    }
}
