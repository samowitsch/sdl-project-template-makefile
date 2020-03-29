#ifndef CGSPRITE_H
#define CGSPRITE_H

#include "CGPoint.h"

class CGSprite
{
public:
    CGSprite(double x = 0, double y = 0);
    ~CGSprite();

    void Draw();
    void Update();
    bool loadTexture(std::string path);

    int width;
    int height;

    int width2;
    int height2;

    double xspeed;
    double xhandle;
    double yspeed;
    double yhandle;

    CGPoint *position;

    double rotation;
    double rotationSpeed;

private:
    SDL_Texture *mTexture;
};

#endif /* CGSPRITE_H */
