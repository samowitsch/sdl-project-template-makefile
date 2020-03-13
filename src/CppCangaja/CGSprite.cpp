/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   CGSprite.cpp
 * Author: csg
 *
 * Created on 23. Januar 2016, 20:07
 */

#include "../Common/CGGlobals.h"

#include "CGSprite.h"
#include <string>

CGSprite::CGSprite() {
    x = 0;
    y = 0;
    xhandle = 0.5;
    yhandle = 0.5;
    rotation = 0;
}


CGSprite::~CGSprite() {
}

void CGSprite::Draw() {
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x - width2, y - height2, width, height};

    //Render to screen
    SDL_RenderCopyEx(renderer, mTexture, NULL, &renderQuad, rotation, NULL, SDL_FLIP_NONE);
}

void CGSprite::Update() {
}

bool CGSprite::LoadTexture(std::string path) {

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
	SDL_Log("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
	//Color key image
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

	//Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (newTexture == NULL) {
	    SDL_Log("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	} else {
	    //Get image dimensions
	    width = loadedSurface->w;
	    height = loadedSurface->h;

	    width2 = width * xhandle;	    //
	    height2 = height * yhandle;
	}

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

