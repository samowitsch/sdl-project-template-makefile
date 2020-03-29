#include "Common/CGIncludes.h"
#include <iostream>
#include <string>
using namespace std;

class CApp {
public:
    // Application state

    enum APP_STATE {
        APP_OK = 0,
        APP_FAILED = 1
    };

    CApp();
    ~CApp();

    // Run application, called by your code.
    int OnExecute();
    int HandleAppEvents(void *userdata, SDL_Event *event);

private:
    // Whether the application is running.
    bool running;

    SDL_Texture *bitmapTex;
    SDL_Surface *bitmapSurface;
    Mix_Music *music;

    SDL_Color fontColor;
    SDL_Rect fontRect;
    SDL_Texture *fontImage;

    int pointerX;
    int pointerY;

    // Initialize application
    int OnInit();

    // Clean up the application
    void OnCleanup();

    // Called to process SDL event.
    void OnEvent(SDL_Event *event);

    // Called to update game logic
    void OnUpdate();

    // Called to render the app.
    void OnRender();

    SDL_Texture *RenderText(
            const std::string &message,
            const std::string &fontFile,
            SDL_Color &color,
            int fontSize,
            SDL_Renderer *renderer);

    void RenderTexture(
            SDL_Texture *tex,
            SDL_Renderer *ren,
            SDL_Rect dst,
            SDL_Rect *clip = nullptr);

    void RenderTexture(
            SDL_Texture *tex,
            SDL_Renderer *ren,
            int x,
            int y,
            SDL_Rect *clip = nullptr);
};