#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "SDL_Basic.h"

SDL_Surface* loadImage(std::string filename)
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load(filename.c_str());

    if(loadedImage != NULL)
    {
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
    }

    return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
    SDL_Rect offset;
    offset.x=x;
    offset.y=y;

    SDL_BlitSurface(source, NULL, destination, &offset);
}

SDL_Surface* init(int SCREEN_WIDTH, int SCREEN_HEIGHT, int SCREEN_BPP)
{
    SDL_Surface* screen = NULL;

    if(SDL_Init( SDL_INIT_EVERYTHING ) == -1)
    {
        return NULL;
    }

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

    // Redundant, but a reminder of what will happen
    if(screen == NULL)
    {
        return NULL;
    }

    return screen;
}

SDL_Surface* init(int SCREEN_WIDTH, int SCREEN_HEIGHT, int SCREEN_BPP, std::string title)
{
    SDL_Surface* screen = NULL;

    if(SDL_Init( SDL_INIT_EVERYTHING ) == -1)
    {
        return NULL;
    }

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

    SDL_WM_SetCaption( title.c_str(), NULL );

    // Redundant, but a reminder of what will happen
    if(screen == NULL)
    {
        return NULL;
    }

    return screen;
}
