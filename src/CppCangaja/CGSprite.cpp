#include "../Common/CGGlobals.h"

#include "CGSprite.h"
#include "CGPoint.h"
#include <string>

#define HANDLE_CENTER 0.5
#define HANDLE_TOP 0
#define HANDLE_BOTTOM 1
#define HANDLE_LEFT 0
#define HANDLE_RIGHT 1

CGSprite::CGSprite(double x, double y)
{
    position = new CGPoint(x, y);
    xspeed = 0;
    xhandle = HANDLE_CENTER;
    yspeed = 0;
    yhandle = HANDLE_CENTER;
    rotation = 0;
    rotationSpeed = 0;
}

CGSprite::~CGSprite()
{
}

void CGSprite::Draw()
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {position->x - width2, position->y - height2, width, height};

    //Render to screen
    SDL_RenderCopyEx(renderer, mTexture, NULL, &renderQuad, rotation, NULL, SDL_FLIP_NONE);
}

void CGSprite::Update()
{
    position->x += xspeed;
    position->y += yspeed;
    rotation = rotation + rotationSpeed;
}

bool CGSprite::loadTexture(std::string path)
{

    //The final texture
    SDL_Texture *newTexture = NULL;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        SDL_Log("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            SDL_Log("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            //Get image dimensions
            width = loadedSurface->w;
            height = loadedSurface->h;

            width2 = width * xhandle;
            height2 = height * yhandle;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}
