/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   CGSprite.h
 * Author: csg
 *
 * Created on 23. Januar 2016, 20:07
 */
#include "Common/CGIncludes.h"


#ifndef CGSPRITE_H
#define CGSPRITE_H

class CGSprite {
public:
    CGSprite();
    ~CGSprite();

    void Draw();
    void Update();
    bool LoadTexture(std::string path);

    int width;
    int height;

    int width2;
    int height2;

    float xhandle;
    float yhandle;

    int x;
    int y;
    float rotation;

private:
    SDL_Texture* mTexture;

};

#endif /* CGSPRITE_H */

